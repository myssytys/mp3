#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Tetra {

	struct Vertex {
		float x, y, z;
		float r, g ,b;
		float nx, ny, nz;
	};

	float cX, cY, cZ;
	float edge;
	Vertex* vertex;
	int *indices;	

	// Constructor
	Tetra(float cX, float cY, float cZ, float edge) {

		
		this->cX = cX;
		this->cY = cY;
		this->cZ = cZ;
		this->edge = edge;

		vertex = new Vertex[12];
		indices = (int*)malloc(12);

	    vertex=new Vertex{
			0.0f, edge, 0.0f,
			edge/2.0f, -edge/2.0f, 0.0f, 
			0.0f, 0.0f, edge,
			-edge/2.0f, -edge/2.0f, 0.0f
			};

		
	   indices={
		 
		    0, 1, 2,  // Face 0
            0, 2, 3,  // Face 1
            0, 3, 1,  // Face 2
            1, 3, 2   // Face 3
	   };
	
	
}
	

	~Tetra() {
		delete vertex;
		delete indices;

	}

	float getCenterX() {
		return cX;
	}
	float getCenterY() {
		return cY;
	}
	float getCenterZ() {
		return cZ;
	}

	void setCenterX(float cx) {
		cX = cx;
	}
	void setCenterY(float cy) {
		cY = cy;
	}
	void setCenterZ(float cz) {
		cZ = cz;
	}
	
	
	

};
