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
	return -K*(1-L/d)*vector; 
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

struct Ball {

    // Propriétés physique des points:
    std::vector<glm::vec3> positionArray;
    std::vector<glm::vec3> vectorArray;
    std::vector<glm::vec3> velocityArray;
    std::vector<float> massArray;
    std::vector<glm::vec3> forceArray;
    static const int nbPoints = 20;
    float m_fElasticity=1.3;
    float radius;

    // Paramètres des forces interne de simulation
    // Longueurs à vide
    float L0,L1,L2,L3;
    float K0, K1, K2,K3; // Paramètres de résistance
    float V0, V1, V2,V3; // Paramètres de frein
    
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

    // Créé boule discrétisée sous forme d'un tétrahèdre avec un point au centre
    // points. Chaque point a pour masse mass / nbPoints .
    Ball(float mass, float radius) :
    	positionArray( (nbPoints-1)*(2*nbPoints)+3), vectorArray( (nbPoints-1)*(2*nbPoints)+3),velocityArray( (nbPoints-1)*(2*nbPoints)+3),
    	massArray( (nbPoints-1)*(2*nbPoints)+3,mass /(nbPoints-1)*(2*nbPoints)+3), forceArray( (nbPoints-1)*(2*nbPoints)+3,glm::vec3(0.f)){

        glm::vec3 origin(0., 0., 0.);
        this->radius=radius;

        // On place le centre dans les tableaux
        positionArray[0] = origin;

        // on place les pôles dans le tableau
        positionArray[1] = glm::vec3(origin.x, origin.y, radius);
        positionArray[2] = glm::vec3(origin.x, origin.y, -radius);

		if(nbPoints>1)
        for(int j = 0; j < 2*nbPoints; ++j) {
            for(int i = 0; i < nbPoints-1; ++i) {
            	float posX = sin(((i+1)*M_PI/nbPoints)) * cos(((j+1)*M_PI/nbPoints));
            	float posY = sin(((i+1)*M_PI/nbPoints)) * sin(((j+1)*M_PI/nbPoints));
            	float posZ = cos(((i+1)*M_PI/nbPoints));
                positionArray[3 + i + j * (nbPoints-1)] = origin + glm::vec3(posX, posY, posZ) * radius;
            }
        }
        for(int i=0;i<positionArray.size();++i)
        {
			vectorArray[i]=positionArray[i]-positionArray[0];
		}

        // Les longueurs à vide sont calculés à partir de la position initiale
        // des points sur le drapeau
        L0=radius/2;
        L1=glm::distance(positionArray[1],positionArray[3]);
        L2=glm::distance(positionArray[3],positionArray[3+nbPoints]);
        L3=glm::distance(positionArray[1],positionArray[4]);


        // Ces paramètres sont à fixer pour avoir un système stable
        K0 = 10.f;
        K1 = 0.0f;
        K2 = 0.0f;
        K3 = 0.0f;

        V0 = 0.0001f;
        V1 = 0.00f;
        V2 = 0.00f;
        V3 = 0.00f;
    }

	ParticleState getNextState(uint32_t dx, float dt)const
	{
		ParticleState state;
		state.speed=(velocityArray[dx]+dt*forceArray[dx]/massArray[dx]);	
		state.position=(positionArray[dx]+dt*velocityArray[dx]);
		return state;
	}
	void ressort(glm::vec3 v)
	{
		forceArray[0]+=hookForce(K0,L0,positionArray[0],v);
	}
    // Applique les forces internes sur chaque point du drapeau SAUF les points fixes
    void applyInternalForces(float dt) {
		
		/*forceArray[0]+=hookForce(K0,L0,positionArray[0],positionArray[1])+brakeForce(V0,dt,velocityArray[0],velocityArray[1]);
		forceArray[1]+=hookForce(K0,L0,positionArray[1],positionArray[0])+brakeForce(V0,dt,velocityArray[1],velocityArray[0]);
		forceArray[0]+=hookForce(K0,L0,positionArray[0],positionArray[2])+brakeForce(V0,dt,velocityArray[0],velocityArray[2]);
		forceArray[2]+=hookForce(K0,L0,positionArray[2],positionArray[0])+brakeForce(V0,dt,velocityArray[2],velocityArray[0]);
		
		if(nbPoints>1)
		for(int i=3; i<forceArray.size();++i)
		{
			forceArray[0]+=hookForce(K0,L0,positionArray[0],positionArray[i])+brakeForce(V0,dt,velocityArray[0],velocityArray[i]);
			forceArray[i]+=hookForce(K0,L0,positionArray[i],positionArray[0])+brakeForce(V0,dt,velocityArray[i],velocityArray[0]);
			
			if((i-3)%(nbPoints-1)==0)
			{
				forceArray[1]+=hookForce(K1,L1,positionArray[1],positionArray[i])+brakeForce(V1,dt,velocityArray[1],velocityArray[i]);
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[1])+brakeForce(V1,dt,velocityArray[i],velocityArray[1]);
			}	
			if((i-4)%(nbPoints-1)==0)
			{
				forceArray[1]+=hookForce(K3,L3,positionArray[1],positionArray[i])+brakeForce(V3,dt,velocityArray[1],velocityArray[i]);
				forceArray[i]+=hookForce(K3,L3,positionArray[i],positionArray[1])+brakeForce(V3,dt,velocityArray[i],velocityArray[1]);
			}		
			if((i-1-nbPoints)%(nbPoints-1)==0 && (i-1-nbPoints)>=0)
			{
				forceArray[2]+=hookForce(K1,L1,positionArray[2],positionArray[i])+brakeForce(V1,dt,velocityArray[2],velocityArray[i]);
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[2])+brakeForce(V1,dt,velocityArray[i],velocityArray[2]);
			}
			if((i-2-nbPoints)%(nbPoints-1)==0 && (i-2-nbPoints)>=0)
			{
				forceArray[2]+=hookForce(K1,L1,positionArray[2],positionArray[i])+brakeForce(V1,dt,velocityArray[2],velocityArray[i]);
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[2])+brakeForce(V1,dt,velocityArray[i],velocityArray[2]);
			}
			if((i-1-nbPoints)%(nbPoints-1)!=0 && (i-1-nbPoints)>=0)
			{
				forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[i+1])+brakeForce(V1,dt,velocityArray[i],velocityArray[i+1]);
				forceArray[i+1]+=hookForce(K1,L1,positionArray[i+1],positionArray[i])+brakeForce(V1,dt,velocityArray[i+1],velocityArray[i]);
				
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
			}
			
			int j=(i+(nbPoints-1)<(nbPoints-1)*(2*nbPoints)+3 )? (i+(nbPoints-1)) : (i-(nbPoints-1)*(2*nbPoints-1));
			forceArray[i]+=hookForce(K1,L1,positionArray[i],positionArray[j])+brakeForce(V1,dt,velocityArray[i],velocityArray[j]);
			forceArray[j]+=hookForce(K1,L1,positionArray[j],positionArray[i])+brakeForce(V1,dt,velocityArray[j],velocityArray[i]);	
			
			int m=(i+2*(nbPoints-1)<(nbPoints-1)*(2*nbPoints)+3 )? (i+2*(nbPoints-1)) : (i-(nbPoints-1)*(2*nbPoints-1)+(nbPoints-1));
			forceArray[i]+=hookForce(K3,L3,positionArray[i],positionArray[m])+brakeForce(V3,dt,velocityArray[i],velocityArray[m]);
			forceArray[m]+=hookForce(K3,L3,positionArray[m],positionArray[i])+brakeForce(V3,dt,velocityArray[m],velocityArray[i]);		
			
		}*/	
		for(int i=1;i<positionArray.size();++i)
        {
			positionArray[i]=positionArray[0]+vectorArray[i];
		}
         
    }


    // Applique une force externe sur chaque point du drapeau SAUF les points fixes
    void applyExternalForce(const glm::vec3& F) {
        // TODO :
        //forceArray[0]+=F;
        /*for(int i=0;i<forceArray.size();++i)
        {
			forceArray[i]+=F;
		}*/
    }
     void applyGravity(const glm::vec3& F) {
        // TODO :
        forceArray[0]+=massArray[0]*F;
       /* for(int i=0;i<forceArray.size();++i)
        {
			forceArray[i]+=massArray[i]*F;
		}*/
    }
    void rebond(float dt){		
		ParticleState state=getNextState(0,dt);
		glm::vec3 normal(0,0,0);
		if(state.position.z<-3)
		{
			normal=glm::vec3 (0.,0.,-1.);
		}
		if(state.position.z>3)
		{
			normal=glm::vec3 (0.,0.,1.);
		}
		if(state.position.x<-4)
		{
			normal=glm::vec3 (-1.,0.,0.);
		}
		if(state.position.x>4)
		{
			normal=glm::vec3 (1.,0.,0.);
		}
		if(state.position.z<-3 || state.position.z>3 || state.position.x<-4 || state.position.x>4){
			float dot=state.speed.x*(-normal.x)+state.speed.y*(-normal.y)+state.speed.z*(-normal.z);
			dot=dot<0?dot:-dot;
			glm::vec3 force=m_fElasticity*dot*massArray[0]/dt*normal;
			forceArray[0]=(forceArray[0]+force);
		}
	}
	void choc(Ball* ball1,float dt)
	{
		ParticleState state=getNextState(0,dt);
		ParticleState state1=(*ball1).getNextState(0,dt);
		float distance=glm::distance(state.position,state1.position);
		//std::cout<<"distance:"<<distance<<"radius:"<<radius<<std::endl;
		if(distance<radius+ball1->radius)
		{
			//std::cout<<"choc"<<std::endl;
			glm::vec3 normal=state.position-state1.position;
			normal=glm::normalize(normal);
			float dot=glm::dot(state.speed,-normal);
			dot=dot<0?dot:-dot;
			glm::vec3 force=m_fElasticity*dot*massArray[0]/dt*normal;
			forceArray[0]=(forceArray[0]-force);
			(*ball1).forceArray[0]=((*ball1).forceArray[0]+force);
			/*float dot1=state1.speed.x*(-normal.x)+state.speed.y*(-normal.y)+state.speed.z*(-normal.z);
			dot=dot<0?dot:-dot;
			glm::vec3 force=m_fElasticity*dot*massArray[0]/dt*normal;
			forceArray[0]=(forceArray[0]+force);*/
		}
	}
			
		
    void update(float dt) {
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

    Ball ball(200, 0.2); // Création d'une balle
    
    Ball ball1(100, 0.1); // Création d'une balle
    ball1.positionArray[0]=glm::vec3(1,0,1);
    Ball ball2(300, 0.3); // Création d'une balle
    ball2.positionArray[0]=glm::vec3(1,0,-1);
    Ball ball3(400, 0.4); // Création d'une balle
    ball3.positionArray[0]=glm::vec3(-1,0,-1);
    Ball ball4(500, 0.5); // Création d'une balle
    ball4.positionArray[0]=glm::vec3(-1,0,1);
    
    //Cube cube(10.f,5.,5.,5.);
    glm::vec3 G(0.f, 0.f, -0.01f); // Gravité

    BallRenderer3D renderer(Ball::nbPoints);
    renderer.setProjMatrix(glm::perspective(70.f, float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f));
    renderer.daBall = 1;

    BallRenderer3D renderer1(Ball::nbPoints);
    renderer1.setProjMatrix(glm::perspective(70.f, float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f));
    BallRenderer3D renderer2(Ball::nbPoints);
    renderer2.setProjMatrix(glm::perspective(70.f, float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f));
    BallRenderer3D renderer3(Ball::nbPoints);
    renderer3.setProjMatrix(glm::perspective(70.f, float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f));
    BallRenderer3D renderer4(Ball::nbPoints);
    renderer4.setProjMatrix(glm::perspective(70.f, float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f));

    TrackballCamera camera;
    int mouseLastX, mouseLastY;

    // Temps s'écoulant entre chaque frame
    float dt = 0.f;

	bool done = false;
    bool wireframe = true;
    int X, Y;
    while(!done) {
        wm.startMainLoop();

        // Rendu
        renderer.clear();
        renderer1.clear();
        renderer2.clear();
        renderer3.clear();
        renderer4.clear();

        renderer.setViewMatrix(camera.getViewMatrix());
        renderer.drawGrid(ball.positionArray.data(), wireframe);
        
        renderer1.setViewMatrix(camera.getViewMatrix());
        renderer1.drawGrid(ball1.positionArray.data(), wireframe);
        renderer2.setViewMatrix(camera.getViewMatrix());
        renderer2.drawGrid(ball2.positionArray.data(), wireframe);
        renderer3.setViewMatrix(camera.getViewMatrix());
        renderer3.drawGrid(ball3.positionArray.data(), wireframe);
        renderer4.setViewMatrix(camera.getViewMatrix());
        renderer4.drawGrid(ball4.positionArray.data(), wireframe);
        SDL_GetMouseState(&X, &Y);
        float x=8*(float)((float)X-(float)WINDOW_WIDTH/2.)/(float)(WINDOW_WIDTH);
        float y=-6*(float)((float)Y-(float)WINDOW_HEIGHT/2.)/(float)(WINDOW_HEIGHT);
        // Simulation
        if(dt > 0.f) {
            //ball.applyGravity(G); // Applique la gravité
            //ball.applyExternalForce(glm::sphericalRand(0.1f)); // Applique un "vent" de direction aléatoire et de force 0.1 Newtons
            ball.applyInternalForces(dt);
            ball1.applyInternalForces(dt);
            ball2.applyInternalForces(dt);
            ball3.applyInternalForces(dt);
            ball4.applyInternalForces(dt); // Applique les forces internes
            //ball.positionArray[0]=glm::vec3(x,0, y);
            ball.ressort(glm::vec3(x,0, y));
            ball.rebond(dt);
            ball1.rebond(dt);
            ball2.rebond(dt);
            ball3.rebond(dt);
            ball4.rebond(dt);
            ball.choc(&ball1,dt);
            ball.choc(&ball2,dt);
            ball.choc(&ball3,dt);
            ball.choc(&ball4,dt);
            ball1.choc(&ball,dt);
            ball1.choc(&ball2,dt);
            ball1.choc(&ball3,dt);
            ball1.choc(&ball4,dt);
            ball2.choc(&ball1,dt);
            ball2.choc(&ball,dt);
            ball2.choc(&ball3,dt);
            ball2.choc(&ball4,dt);
            ball3.choc(&ball1,dt);
            ball3.choc(&ball2,dt);
            ball3.choc(&ball,dt);
            ball3.choc(&ball4,dt);
            ball4.choc(&ball1,dt);
            ball4.choc(&ball2,dt);
            ball4.choc(&ball3,dt);
            ball4.choc(&ball,dt);
            ball.update(dt);            
            ball1.update(dt);
            ball2.update(dt);
            ball3.update(dt);
            ball4.update(dt);
        }
        //std::cout<<"mouse:("<<X<<","<<Y<<")"<<"; position:("<<x<<","<<y<<")"<<std::endl;
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
						ball.setElasticity(0.1);	
						ball1.setElasticity(0.1);
						ball2.setElasticity(0.1);
						ball3.setElasticity(0.1);
						ball4.setElasticity(0.1);
					}
					if(e.key.keysym.sym == SDLK_z)
					{
						ball.setElasticity(-0.1);	
						ball1.setElasticity(-0.1);
						ball2.setElasticity(-0.1);
						ball3.setElasticity(-0.1);
						ball4.setElasticity(-0.1);
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
		int mouseX,mouseY;
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
