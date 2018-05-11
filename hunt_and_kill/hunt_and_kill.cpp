// Includes
#include <stdlib.h>
#include <time.h>

// Function declerations
void createMaze(int start, int* maze, const int* size);
void createRoute(int x, int y, int* maze, const int* size);

// Global variables
const int size = 12;
int maze[size][size];

// Start of the program
int main()
{
	// Get new seed for rand
	srand(time(NULL));

	// Initialize maze
	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			maze[x][y] = 1;

	/* Find out if the size is even or uneven, create start and end in the maze,
	call the createMaze method with the correct start value for the loops corrosponding to even/uneven */
	if (size % 2 == 0) {
		maze[2][2] = 0;
		maze[1][2] = 0;
		maze[0][2] = 2;
		maze[size - 1][size - 2] = 3;
		createMaze(2, (int*)maze, &size);
	}
	else {
		maze[1][1] = 0;
		maze[0][1] = 2;
		maze[size - 1][size - 2] = 3;
		createMaze(1, (int*)maze, &size);
	}

	// End of the program
	return 0;
}

/* While there are possible routes we will open up the connection between two parts of the maze and
create a route linked to this new connection using the createRoute function */
void createMaze(int start, int* maze, const int* size) {
	bool updated = true;

	while (updated) {
		updated = false;
		for (int y = start; y < *size - 1; y += 2) {
			for (int x = start; x < *size - 1; x += 2) {
				if (*(maze + y * *size + x) == 0) {
					if (x > 2) {
						if (*(maze + y * *size + (x - 2)) == 1) {
							*(maze + y * *size + (x - 1)) = 0;
							*(maze + y * *size + (x - 2)) = 0;
							createRoute(x - 2, y, (int*)maze, size);
							updated = true;
						}
					}
					if (x < *size - 2) {
						if (*(maze + y * *size + (x + 2)) == 1) {
							*(maze + y * *size + (x + 1)) = 0;
							*(maze + y * *size + (x + 2)) = 0;
							createRoute(x + 2, y, (int*)maze, size);
							updated = true;
						}
					}
					if (y > 2) {
						if (*(maze + (y - 2) * *size + x) == 1) {
							*(maze + (y - 1) * *size + x) = 0;
							*(maze + (y - 2) * *size + x) = 0;
							createRoute(x, y - 2, (int*)maze, size);
							updated = true;
						}
					}
					if (y < *size - 2) {
						if (*(maze + (y + 2) * *size + x) == 1) {
							*(maze + (y + 1) * *size + x) = 0;
							*(maze + (y + 2) * *size + x) = 0;
							createRoute(x, y + 2, (int*)maze, size);
							updated = true;
						}
					}
				}
			}
		}
	}
}

/* Create a new route in the maze using a starting x and y coordinate and use rand to get directions
to open up parts of the maze for the new route */
void createRoute(int x, int y, int* maze, const int* size) {
	while (*(maze + y * *size + (x - 2)) == 1 && x > 2 || *(maze + y * *size + (x + 2)) == 1 && x < *size - 2 || *(maze + (y - 2) * *size + x) == 1 && y > 2 || *(maze + (y + 2) * *size + x) == 1 && y < *size - 2) {
		switch (rand() % 4) {
		case 0:
			if (*(maze + y * *size + (x - 2)) == 1 && x > 2) {
				*(maze + y * *size + (x - 1)) = 0;
				*(maze + y * *size + (x - 2)) = 0;
				x -= 2;
			}
			break;
		case 1:
			if (*(maze + (y - 2) * *size + x) == 1 && y > 2) {
				*(maze + (y - 1) * *size + x) = 0;
				*(maze + (y - 2) * *size + x) = 0;
				y -= 2;
			}
			break;
		case 2:
			if (*(maze + (y + 2) * *size + x) == 1 && y < *size - 2) {
				*(maze + (y + 1) * *size + x) = 0;
				*(maze + (y + 2) * *size + x) = 0;
				y += 2;
			}
			break;
		case 3:
			if (*(maze + y * *size + (x + 2)) == 1 && x < *size - 2) {
				*(maze + y * *size + (x + 1)) = 0;
				*(maze + y * *size + (x + 2)) = 0;
				x += 2;
			}
			break;
		}
	}
	return;
}