#include <iostream>
#include <cstdlib>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer/WindowManager.hpp"
#include "renderer/BallRenderer3D.hpp"
#include "renderer/TrackballCamera.hpp"

#include <vector>

static const Uint32 WINDOW_WIDTH = 1024;
static const Uint32 WINDOW_HEIGHT = 768;

using namespace imac3;


//////////////////////////////////////////////////////////////////
//                          BOF UTILS                           //
//////////////////////////////////////////////////////////////////
//|
//|
//| Calcule une force de type ressort de Hook entre deux particules de positions P1 et P2
//| K est la résistance du ressort et L sa longueur à vide
inline glm::vec3 hookForce(float K, float L, const glm::vec3& P1, const glm::vec3& P2) {
    static const float epsilon = 0.0001;
    glm::vec3 vector=P1-P2;
	float d=glm::distance(P1,P2);
	d=(d<epsilon)?epsilon:d;
	return K*(1-L/d)*vector; 
}

//| Calcule une force de type frein cinétique entre deux particules de vélocités v1 et v2
//| V est le paramètre du frein et dt le pas temporel
inline glm::vec3 brakeForce(float V, float dt, const glm::vec3& v1, const glm::vec3& v2) {
    glm::vec3 vector=v1-v2;
	return V*vector/dt;
}
//|
//////////////////////////////////////////////////////////////////
//                          EOF UTILS                           //
//////////////////////////////////////////////////////////////////
struct ParticleState{
	glm::vec3 speed;
	glm::vec3 position;
};

//////////////////////////////////////////////////////////////////
//                      BOF STRUCT BALL                         //
//////////////////////////////////////////////////////////////////
//|
//| Structure permettant de simuler un drapeau à l'aide un système masse-ressort
//|
/*struct Cube{
	std::vector<glm::vec3> positionArray;
    std::vector<glm::vec3> velocityArray;
    std::vector<float> massArray;
    std::vector<glm::vec3> forceArray;
    
    glm::vec3 origin=glm::vec3(0.f)
    
     Cube(float mass, float width, float lenght, float height) :
    	positionArray(8), velocityArray(3),
    	massArray(8,mass /(8), forceArray( 8,glm::vec3(0.f)){
			
		positionArray[0]=glm::vec3(-width/2,-lenght/2,-height/2);
		positionArray[1]=glm::vec3(-width/2,lenght/2,-height/2);
		positionArray[2]=glm::vec3(width/2,lenght/2,-height/2);
		positionArray[3]=glm::vec3(width/2,-lenght/2,-height/2);
			
		positionArray[4]=glm::vec3(-width/2,-lenght/2,height/2);
		positionArray[5]=glm::vec3(-width/2,lenght/2,height/2);
		positionArray[6]=glm::vec3(width/2,lenght/2,height/2);
		positionArray[7]=glm::vec3(width/2,-lenght/2,height/2);		
	}
	
};*/
struct Ball {

    // Propriétés physique des points:
    std::vector<glm::vec3> positionArray;
    std::vector<glm::vec3> velocityArray;
    std::vector<float> massArray;
    std::vector<glm::vec3> forceArray;
    static const int nbPoints = 100;

    // Paramètres des forces interne de simulation
    // Longueurs à vide
    float L0,L1,L2;
    float K0, K1, K2; // Paramètres de résistance
    float V0, V1, V2; // Paramètres de frein

    // Créé boule discrétisée sous forme d'un tétrahèdre avec un point au centre
    // points. Chaque point a pour masse mass / nbPoints .
    Ball(float mass, float radius) :
    	positionArray( (nbPoints-1)*(2*nbPoints)+3), velocityArray( (nbPoints-1)*(2*nbPoints)+3),
    	massArray( (nbPoints-1)*(2*nbPoints)+3,mass /(nbPoints-1)*(2*nbPoints)+3), forceArray( (nbPoints-1)*(2*nbPoints)+3,glm::vec3(0.f)){

        glm::vec3 origin(0., 0., 0.);

        // On place le centre dans les tableaux
        positionArray[0] = origin;

        // on place les pôles dans le tableau
        positionArray[1] = glm::vec3(origin.x, origin.y, radius);
        positionArray[2] = glm::vec3(origin.x, origin.y, -radius);

        for(int j = 0; j < 2*nbPoints; ++j) {
            for(int i = 0; i < nbPoints-1; ++i) {
            	float posX = sin(((i+1)*M_PI/nbPoints)) * cos(((j+1)*M_PI/nbPoints));
            	float posY = sin(((i+1)*M_PI/nbPoints)) * sin(((j+1)*M_PI/nbPoints));
            	float posZ = cos(((i+1)*M_PI/nbPoints));
                positionArray[3 + i + j * (nbPoints-1)] = origin + glm::vec3(posX, posY, posZ) * radius;
            }
        }

        // Les longueurs à vide sont calculés à partir de la position initiale
        // des points sur le drapeau
        L0=radius;
        L1=glm::distance(positionArray[1],positionArray[3]);
        L2=glm::distance(positionArray[3],positionArray[3+nbPoints]);


        // Ces paramètres sont à fixer pour avoir un système stable
        K0 = 1.f;
        K1 = 1.f;
        K2 = 1.f;

        V0 = 0.f;
        V1 = 0.f;
        V2 = 0.1f;
    }

	ParticleState getNextState(uint32_t dx, float dt)const
	{
		ParticleState state;
		state.speed=(velocityArray[dx]+dt*forceArray[dx]/massArray[dx]);	
		state.position=(positionArray[dx]+dt*velocityArray[dx]);
		return state;
	}

    // Applique les forces internes sur chaque point du drapeau SAUF les points fixes
    void applyInternalForces(float dt) {
		
		forceArray[0]+=hookForce(K0,L0,positionArray[0],positionArray[1])+brakeForce(V0,dt,velocityArray[0],velocityArray[1]);
		forceArray[1]+=hookForce(K0,L0,positionArray[1],positionArray[0])+brakeForce(V0,dt,velocityArray[1],velocityArray[0]);
		forceArray[0]+=hookForce(K0,L0,positionArray[0],positionArray[2])+brakeForce(V0,dt,velocityArray[0],velocityArray[2]);
		forceArray[2]+=hookForce(K0,L0,positionArray[2],positionArray[0])+brakeForce(V0,dt,velocityArray[2],velocityArray[0]);
			
		for(int i=3; i<forceArray.size();++i)
		{
			forceArray[0]+=hookForce(K0,L0,positionArray[0],positionArray[i])+brakeForce(V0,dt,velocityArray[0],velocityArray[i]);
			forceArray[i]+=hookForce(K0,L0,positionArray[i],positionArray[0])+brakeForce(V0,dt,velocityArray[i],velocityArray[0]);
			
			if((i-3)%(nbPoints-1)==0)
			{
				forceArray[1]+=hookForce(K1,L1,positionArray[1],positionArray[i])+brakeForce(V1,dt,velocityArray[1],velocityArray[i]);
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[1])+brakeForce(V1,dt,velocityArray[i],velocityArray[1]);
			}			
			if((i-2-nbPoints)%(nbPoints-1)==0)
			{
				forceArray[2]+=hookForce(K1,L1,positionArray[2],positionArray[i])+brakeForce(V1,dt,velocityArray[2],velocityArray[i]);
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[2])+brakeForce(V1,dt,velocityArray[i],velocityArray[2]);
			}
			if((i-2-nbPoints)%(nbPoints-1)==0)
			{
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[i+1])+brakeForce(V1,dt,velocityArray[i],velocityArray[i+1]);
				forceArray[i+1]+=hookForce(K1,L1,positionArray[i+1],positionArray[i])+brakeForce(V1,dt,velocityArray[i+1],velocityArray[i]);
			}	
			
			int j=(i+(nbPoints-1)<(nbPoints-1)*(2*nbPoints)+3 )? (i+(nbPoints-1)) : ((i-2)%(nbPoints-1)+3);
			forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[j])+brakeForce(V1,dt,velocityArray[i],velocityArray[j]);
			forceArray[j]+=hookForce(K1,L1,positionArray[j],positionArray[i])+brakeForce(V1,dt,velocityArray[j],velocityArray[i]);
			
		}		
         
    }


    // Applique une force externe sur chaque point du drapeau SAUF les points fixes
    void applyExternalForce(const glm::vec3& F) {
        // TODO :
        for(int i=0;i<forceArray.size();++i)
        {
			forceArray[i]+=F;
		}
    }
    void rebond(float dt){
		for(int i=0;i<forceArray.size();i++)
		{
			ParticleState state=getNextState(i,dt);
			if(state.position.y<-1)
			{
				glm::vec3 normal(0.,-1.,0.);
				float m_fElasticity=2;
				float dot=state.speed.x*(-normal.x)+state.speed.y*(-normal.y);
				//printf("dot:%f->speed: %f,%f; normal:%f,%f \n\n",dot,state.speed.x,state.speed.y,normal.x,normal.y);
				glm::vec3 force=m_fElasticity*dot*massArray[i]/dt*normal;
				//printf("collide %i: next force: %f,%f, elasticity:%f,dot:%f,mass:%f,dt:%f, normal:%f%f:",i,pm.arr_force[i].x,pm.arr_force[i].y,m_fElasticity,dot,pm.arr_mass[i],m_fDt,normal.x,normal.y);
				forceArray[i]=(forceArray[i]+force);
				//printf(" new force: %f,%f \n\n",pm.arr_force[i].x,pm.arr_force[i].y);
			}
			
		}
	}

    // Met à jour la vitesse et la position de chaque point du drapeau
    // en utilisant un schema de type Leapfrog
    void update(float dt) {
        // TODO
        // Ne pas oublier de remettre les forces à 0 !
        for(int i=0;i<forceArray.size();i++)
		{
			velocityArray[i]=(velocityArray[i]+dt*forceArray[i]/massArray[i]);
			
			positionArray[i]=(positionArray[i]+dt*velocityArray[i]);
			
			forceArray[i]=glm::vec3(0,0,0);			
		}
    }
};
//|
//////////////////////////////////////////////////////////////////
//                      EOF STRUCT BALL                         //
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//                            MAIN                              //
//////////////////////////////////////////////////////////////////
//|
int main() {
    WindowManager wm(WINDOW_WIDTH, WINDOW_HEIGHT, "Newton was a Geek");
    wm.setFramerate(30);

    Ball ball(100000.f, 0.2); // Création d'une balle
    
    //Cube cube(10.f,5.,5.,5.);
    glm::vec3 G(0.f, -10000.f, 0.f); // Gravité

    BallRenderer3D renderer(Ball::nbPoints);
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
        renderer.clear();

        renderer.setViewMatrix(camera.getViewMatrix());
        renderer.drawGrid(ball.positionArray.data(), wireframe);

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
