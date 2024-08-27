#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

void initialize(int**, int, int); // setting up the table for the first level
int alives_around(int**, int, int, int); // counts the alive neighbours of an specific coordinate

int main()
{
	sf::RenderWindow window(sf::VideoMode(480, 540), "The Game Of Life"); // window setup
	sf::Event event;
	
	window.clear(sf::Color(50, 50, 50, 255)); // window background color
	
	sf::Image image; // defining image
	image.create(400, 400, sf::Color::Black); // this is a 400 * 400 (pixels) image which we will move on pixels 4 by 4, so it will become a 100 * 100 table with 10000 cells
	sf::Color black(0, 0, 0, 255);
	sf::Color green(0, 255, 0, 255);
	sf::Color gray(50, 50, 50, 255);
	
	for (int i = 0; i < 400; i += 4)
		for (int j = 0; j < 400; j++)
			image.setPixel(j, i, gray); // creating cells
	
	for (int i = 0; i < 400; i++)
		for (int j = 0; j < 400; j += 4)
			image.setPixel(j, i, gray); // creating cells

	int n = 100, FirstAlive; // FirstAlive: cells which are alive in the first level
/***/	FirstAlive = (rand() % 30) + 5000; // a random number for the alive cells in the first level
	
	int** table = new int*[n]; // main game table array (100 * 100)
	for (int i = 0; i < n; i++)
		table[i] = new int[n];
		
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			table[i][j] = 0;
	
	initialize(table, n, FirstAlive); // initializing the table for the first level 
	// the alive elements will hold the value 1 and the dead ones will hold 0
	
	for (int x = 0; x < n; x++) // displaying first alive cells
	{
		for (int y = 0; y < n; y++)
		{
			if (table[x][y] == 1)
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
						image.setPixel((y * 4) + i, (x * 4) + j, green); // converting the coordinate in array to ccordinate in table
				}
		}
	}
		
	int** dead_cells = new int*[n * n]; // this array will hold the coordinates of the alive cells which will be dead in the next level
	for (int i = 0; i < (n * n); i++)
		dead_cells[i] = new int[2];
	int dead_index = 0;
	
	int** healed_cells = new int*[n * n]; // this array will hold the coordinates of the dead cells which will become alive in the next level
	for (int i = 0; i < (n * n); i++)
		healed_cells[i] = new int[2];
	int healed_index = 0;
	
	// setting up the structure of the first level
	sf::Texture texture;		
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);
	sprite.setPosition(40.0f, 55.0f); 
	
	// displays the first level
	window.clear(sf::Color(50, 50, 50, 255)); 
	window.draw(sprite);
	window.display();
				
	int x, y;
/***/	int level = 10; // number of the levels that the program will continue			
	
	while (window.isOpen()) // this loop is defined for keeping the window open
	{
/***/		window.setFramerateLimit(15);
		
		while (1)
		{
			for (int i = 0; i < n; i++) // the table will be scanned to identify the cells
			{
				for (int j = 0; j < n; j++)
				{
					if (table[i][j] == 1)
					{
						if (alives_around(table, n, i, j) < 2 || alives_around(table, n, i, j) > 3)
						{	// the coordinates of the cells which will be dead in the next level are added to the array
							dead_cells[dead_index][0] = i; 
							dead_cells[dead_index][1] = j;
							dead_index++; // index of the added cell
						}
					}
					
					if (table[i][j] == 0 && alives_around(table, n, i, j) == 3)
					{	// the coordinates of the dead cells which will become alive in the next level are added to the array
							healed_cells[healed_index][0] = i;
							healed_cells[healed_index][1] = j;
							healed_index++; // index of the added cell
					}
				}
			}
			dead_index--;
			healed_index--;
			for (; dead_index >= 0; dead_index--) 
			{
				x = dead_cells[dead_index][0];
				y = dead_cells[dead_index][1];
				table[x][y] = 0;	// the coordinates stored in the array "dead_cells" become dead
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
						image.setPixel((y * 4) + i, (x * 4) + j, black); // the coordinates of the array elements are converted to the ccordinates of the cells
				}
			}
			dead_index = 0;
			
			for (;healed_index >= 0; healed_index--)
			{
				x = healed_cells[healed_index][0];
				y = healed_cells[healed_index][1];
				table[x][y] = 1;	// the coordinates stored in the array "healed_cells" become alive
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
						image.setPixel((y * 4) + i, (x * 4) + j, green); // the coordinates of the array elements are converted to the ccordinates of the cells
				}
			}
			healed_index = 0;
			
			level--;
			
			for (int i = 0; i < 400; i += 4)
				for (int j = 0; j < 400; j++)
					image.setPixel(j, i, gray); // drawing the cells
	
			for (int i = 0; i < 400; i++)
				for (int j = 0; j < 400; j += 4)
					image.setPixel(j, i, gray); // drawing the cells
	
			sf::Texture texture; // the texture is refreshed in each level
			texture.loadFromImage(image);
			sf::Sprite sprite(texture);
			sprite.setPosition(40.0f, 55.0f);
				
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close(); // if you click on the "close" button the window will be closed
					return 0;
				}
				else if (event.type == sf::Event::KeyPressed)
					if (event.key.code == sf::Keyboard::Escape)
					{
						window.close(); // if you press the "Escape" button the window will be closed
						return 0;
					}
			}	
			// the window is refreshed in each level 
			window.clear(sf::Color(50, 50, 50, 255)); // the window will be cleared
			window.draw(sprite); // and the next level will be displayed
			window.display();
		}
		return 0;
	}
	return 0;
}


void initialize(int** table, int size, int FirstAlive) // setting up the table for the first level
{
	int x, y;
	srand(time(0));
	while(FirstAlive > 0)
	{
		// each time a random coordinate is generated
		x = rand() % size;
		y = rand() % size;
		if (table[x][y] == 1) // if it was alive, a new one will be generated
			continue;
		else // if it was dead ... 
		{
			table[x][y] = 1; // ... then its value will be set to 1
			FirstAlive--; // the remainig cells that must be filled
		}
	}
}

int alives_around(int** table, int size, int x, int y) // counts the alive neighbours of an specific coordinate
{
	int counter = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (i < 0)
			continue;
		if (i >= size)
			break;
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (j < 0)
				continue;
			if (j >= size)
				break;
			if (i == x && j == y)
				continue;
			if (table[i][j] == 1)
				counter++;
		}
	}
	return counter;
}