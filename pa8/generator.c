/*
 * generator.c
 * Cooper Harris
 * CSC 352
 * 
 * This program uses the file 3d.c to add pyramids to a Scene3D and write that
 * scene to an STL file. It uses a for loop and several ints to set the intial values
 * of Coordinate3Ds which are used to make the pyramids. After it writes the pyramids 
 * to the STL file it frees all memory associated with the scene using the destroy function
 * from 3d.c.
 */

#include "3d.h"

int main() {
	Scene3D* star = Scene3D_create(); 

	int x = 100, y = 100, z = 100, a = 100;
	int width = 20;
	for (int i = 0; i <= 5; i ++) {
	       	Coordinate3D o = {100, x, z};
	       	Coordinate3D p = {100, y, a};
	       	Coordinate3D q = {x, 100, z};
	       	Coordinate3D r = {y, 100, a};


		Scene3D_add_pyramid(star, o, width, 30, "forward");
		Scene3D_add_pyramid(star, p, width, 30, "backward");

		Scene3D_add_pyramid(star, q, width, 30, "left");
		Scene3D_add_pyramid(star, r, width, 30, "right");

		
		x += 20;
		y -= 20;	
		z += 30;
		a -= 30;
		width += 20;
	} 

	Scene3D_write_stl_text(star, "output.stl");

	Scene3D_destroy(star);

	return 0;
}
