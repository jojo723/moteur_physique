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


    std::vector<glm::vec3> vectorArray;
    float m_fElasticity=3;
    
    void setElasticity(float a)
    {
		m_fElasticity+=a;
	}
	void setL(float a)
    {
		L0+=a;
	}
	void setK(float a)
    {
		K0+=a;
	}
		if(nbPoints>1)
        for(int i=0;i<positionArray.size();++i)
        {
			vectorArray[i]=positionArray[i]-positionArray[0];
		}
        L3=glm::distance(positionArray[1],positionArray[4]);
        K3 = 0.0f;
        V3 = 0.00f;
	{
		forceArray[0]+=hookForce(K0,L0,positionArray[0],glm::vec3(0,0,-2));
	}
		if(nbPoints>1)
			{
				forceArray[1]+=hookForce(K3,L3,positionArray[1],positionArray[i])+brakeForce(V3,dt,velocityArray[1],velocityArray[i]);
				forceArray[i]+=hookForce(K3,L3,positionArray[i],positionArray[1])+brakeForce(V3,dt,velocityArray[i],velocityArray[1]);
			}		
			if((i-1-nbPoints)%(nbPoints-1)==0 && (i-1-nbPoints)>=0)
			{
				forceArray[2]+=hookForce(K1,L1,positionArray[2],positionArray[i])+brakeForce(V1,dt,velocityArray[2],velocityArray[i]);
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[2])+brakeForce(V1,dt,velocityArray[i],velocityArray[2]);
			}
			if((i-1-nbPoints)%(nbPoints-1)!=0 && (i-1-nbPoints)>=0)
				
				int k=(i-nbPoints<3 )? (i-nbPoints+(nbPoints-1)*(2*nbPoints-1)):i-nbPoints;
				forceArray[i]+=hookForce(K2,L2,positionArray[i],positionArray[k])+brakeForce(V2,dt,velocityArray[i],velocityArray[k]);
				forceArray[k]+=hookForce(K2,L2,positionArray[k],positionArray[i])+brakeForce(V2,dt,velocityArray[k],velocityArray[i]);
				
				int l=(i+nbPoints>(nbPoints-1)*(2*nbPoints)+3 )? i+nbPoints-(nbPoints-1)*(2*nbPoints-1):i+nbPoints;
				forceArray[i]+=hookForce(K2,L2,positionArray[i],positionArray[l])+brakeForce(V2,dt,velocityArray[i],velocityArray[l]);
				forceArray[l]+=hookForce(K2,L2,positionArray[l],positionArray[i])+brakeForce(V2,dt,velocityArray[l],velocityArray[i]);
				
				if((i-2-nbPoints)%(nbPoints-1)!=0 && (i-2-nbPoints)>=0)
				{
					forceArray[i+2]+=hookForce(K3,L3,positionArray[i+2],positionArray[i])+brakeForce(V3,dt,velocityArray[i+2],velocityArray[i]);
					forceArray[i]+=hookForce(K3,L3,positionArray[i],positionArray[i+2])+brakeForce(V3,dt,velocityArray[i],velocityArray[i+2]);
				}
			int m=(i+2*(nbPoints-1)<(nbPoints-1)*(2*nbPoints)+3 )? (i+2*(nbPoints-1)) : (i-(nbPoints-1)*(2*nbPoints-1)+(nbPoints-1));
			forceArray[i]+=hookForce(K3,L3,positionArray[i],positionArray[m])+brakeForce(V3,dt,velocityArray[i],velocityArray[m]);
			forceArray[m]+=hookForce(K3,L3,positionArray[m],positionArray[i])+brakeForce(V3,dt,velocityArray[m],velocityArray[i]);		
			
		}	*/
		for(int i=1;i<positionArray.size();++i)
        {
			positionArray[i]=positionArray[0]+vectorArray[i];
        /*for(int i=0;i<forceArray.size();++i)
		}*/
     void applyGravity(const glm::vec3& F) {
        // TODO :
        forceArray[0]+=massArray[0]*F;
        /*for(int i=0;i<forceArray.size();++i)
        {
			forceArray[i]+=massArray[i]*F;
		}*/
			ParticleState state=getNextState(0,dt);
			if(state.position.z<-2)
				float dot=state.speed.x*(-normal.x)+state.speed.y*(-normal.y)+state.speed.z*(-normal.z);
				dot=dot<0?dot:-dot;
				//printf("dot:%f->speed: %f,%f; normal:%f,%f \n\n",dot,state.speed.x,state.speed.y,normal.x,normal.y);
				glm::vec3 force=m_fElasticity*dot*massArray[0]/dt*normal;
				//printf("collide %i: next force: %f,%f, elasticity:%f,dot:%f,mass:%f,dt:%f, normal:%f%f:",i,pm.arr_force[i].x,pm.arr_force[i].y,m_fElasticity,dot,pm.arr_mass[i],m_fDt,normal.x,normal.y);
				forceArray[0]=(forceArray[0]+force);
				//printf(" new force: %f,%f \n\n",pm.arr_force[i].x,pm.arr_force[i].y);
			}
			
			/*if(state.position.y>1)
			

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
    float dt = 0.f;

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
            ball.applyGravity(G); // Applique la gravité
           // ball.applyExternalForce(glm::sphericalRand(0.1f)); // Applique un "vent" de direction aléatoire et de force 0.1 Newtons
            ball.applyInternalForces(dt); // Applique les forces internes
            ball.ressort();
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
                case SDL_KEYDOWN:
					if(e.key.keysym.sym == SDLK_SPACE) {
                        wireframe = !wireframe;
                    }
					if(e.key.keysym.sym == SDLK_UP)
					{
						ball.setL(1);	
					}
					if(e.key.keysym.sym == SDLK_DOWN)
					{
						ball.setL(-1);	
					}
					if(e.key.keysym.sym == SDLK_a)
					{
						ball.setElasticity(1);	
					}
					if(e.key.keysym.sym == SDLK_z)
					{
						ball.setElasticity(-1);	
					}
					if(e.key.keysym.sym == SDLK_LEFT)
					{
						ball.setK(1);	
					}
					if(e.key.keysym.sym == SDLK_RIGHT)
					{
						ball.setK(-1);	
					}
					std::cout<<"K:"<<ball.K0<<"L:"<<ball.L0<<"Elasticity:"<<ball.m_fElasticity<<std::endl;
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
