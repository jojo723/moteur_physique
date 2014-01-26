#include <iostream>
#include <cstdlib>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer/WindowManager.hpp"
#include "renderer/BallRenderer3D.hpp"
#include "renderer/TrackballCamera.hpp"
#include "renderer/Ball.hpp"

#include <vector>

static const Uint32 WINDOW_WIDTH = 1024;
static const Uint32 WINDOW_HEIGHT = 768;

using namespace imac3;



//////////////////////////////////////////////////////////////////
//                            MAIN                              //
//////////////////////////////////////////////////////////////////
//|
int main() {
    WindowManager wm(WINDOW_WIDTH, WINDOW_HEIGHT, "Newton was a Geek");
    wm.setFramerate(30);

    Ball ball(10, 100000.f, 0.2); // Création d'une balle
    
    //Cube cube(10.f,5.,5.,5.);
    glm::vec3 G(0.f, -2.f, 0.f); // Gravité

    BallRenderer3D renderer(ball);
    renderer.setProjMatrix(glm::perspective(70.f, float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f));

    TrackballCamera camera;
    int mouseLastX, mouseLastY;

    // Temps s'écoulant entre chaque frame
    float dt = 0.01f;

	bool done = false;
    bool wireframe = true;
    while(!done) {
        wm.startMainLoop();

        // Rendu
        Renderer3D::clear();

        renderer.setViewMatrix(camera.getViewMatrix());
        renderer.draw(wireframe);

        // Simulation
        if(dt > 0.f) {
            ball.applyExternalForce(G); // Applique la gravité
           // ball.applyExternalForce(glm::sphericalRand(0.1f)); // Applique un "vent" de direction aléatoire et de force 0.1 Newtons
            ball.applyInternalForces(dt); // Applique les forces internes
            ball.rebond(dt);
            ball.update(dt); // Mise à jour du système à partir des forces appliquées
        }
		/*std::cout<<"position:("<<ball.positionArray[0].x<<ball.positionArray[0].y<<ball.positionArray[0].z
		<<") force: ("<<ball.forceArray[0].x<<ball.forceArray[0].y<<ball.forceArray[0].z
		<<") vitesse: ("<<ball.velocityArray[0].x<<ball.velocityArray[0].y<<ball.velocityArray[0].z<<std::endl;*/
        // Gestion des evenements
		SDL_Event e;
        while(wm.pollEvent(e)) {
			switch(e.type) {
				default:
					break;
				case SDL_QUIT:
					done = true;
					break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_SPACE) {
                        wireframe = !wireframe;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_WHEELUP) {
                        camera.moveFront(0.1f);
                    } else if(e.button.button == SDL_BUTTON_WHEELDOWN) {
                        camera.moveFront(-0.1f);
                    } else if(e.button.button == SDL_BUTTON_LEFT) {
                        mouseLastX = e.button.x;
                        mouseLastY = e.button.y;
                    }
                    break;
			}
		}

        int mouseX, mouseY;
        if(SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            int dX = mouseX - mouseLastX, dY = mouseY - mouseLastY;
            camera.rotateLeft(dX);
            camera.rotateUp(dY);
            mouseLastX = mouseX;
            mouseLastY = mouseY;
        }

        // Mise à jour de la fenêtre
        dt = wm.update();
	}

	return EXIT_SUCCESS;
}
