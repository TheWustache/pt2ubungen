#include <iostream>
#include <ctime>
#include "bitmap_image.hpp"

struct Raster {
	Raster(int w, int h) : width(w), height(h)
	{
		data = new int[width*height];
	}

	Raster(int w, int h, float seedProbability) : width(w), height(h)
	{
		data = new int[width*height];

		// Todo 4.1a: Fill randomly
		// Probability of value 1 is seedProbability, otherwise value is 0
	}

	Raster(const std::string &filename)
	{
		bitmap_image image(filename);

		if (!image)
		{
			std::cerr << "Could not open bitmap!" << std::endl;
		}

		height = image.height();
		width = image.width();

		data = new int[width*height];

		// Todo 4.1a: Load image by using image.get_pixel
		// A black pixel represents 1, all other values represent 0
	}

	void save(const std::string &filename)
	{
		// Todo 4.1a: Save image by using image.set_pixel
		// Living cells should be stored as black pixels, all other pixels are white
		bitmap_image image(width, height);

		image.save_image(filename);
	}

	~Raster()
	{
		delete[] data;
	}

	int width;
	int height;
	int* data;
};

// This struct parses all necessary command line parameters. It is already complete and doesn't have to be modified. However - feel free to add support for additional arguments if you like.
struct CommandLineParameter
{
	CommandLineParameter(int argc, char* argv[])
		: width(0)
		, height(0)
		, invasionFactor(0)
		, isTorus(false)
		, maxIterations(20)
	{
		if (argc % 2 == 0)
		{
			std::cerr << "Missing value for " << argv[argc - 1] << std::endl;
			argc--;
		}

		for (int i = 1; i < argc; i += 2)
		{
			if (!strcmp(argv[i], "-w"))
			{
				width = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-h"))
			{
				height = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-s"))
			{
				seedProbability = static_cast<float>(atof(argv[i + 1]));
			}
			else if (!strcmp(argv[i], "-p"))
			{
				patternFilename = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-o"))
			{
				outputDirectory = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-iv"))
			{
				invasionFactor = static_cast<float>(atof(argv[i + 1]));
			}
			else if (!strcmp(argv[i], "-t"))
			{
				isTorus = strcmp(argv[i + 1], "0") != 0;
			}
			else if (!strcmp(argv[i], "-i"))
			{
				maxIterations = atoi(argv[i + 1]);
			}
		}

		if ((width != 0 || height != 0) && !patternFilename.empty())
		{
			std::cout << "Width and height are ignored, because pattern is defined." << std::endl;
		}

		if (width < 0 || height < 0)
		{
			std::cerr << "Width or height has a invalid value." << std::endl;
			width = 0;
			height = 0;
		}
	}

	int width;
	int height;
	float seedProbability;
	std::string patternFilename;
	std::string outputDirectory;
	float invasionFactor;
	bool isTorus;
	int maxIterations;
};

int neighborValue(const Raster &raster, int x, int y, bool isTorus)
{
	// Todo 4.1b: Return number of living neighbors.
	// In case isTorus is false and (x, y) is outside of raster, return 0
	// In case isTorus is true and (x, y) is outside of raster use value of matching cell of opposite side

	return 0;
}

void simulateInvasion(Raster &raster, float invasionFactor)
{
	if (invasionFactor <= 0)
	{
		return;
	}

	// Todo 4.1c: Flip random some cells (probability to flip for each cell is invasionFactor)
}

void simulateNextState(Raster &raster, bool isTorus)
{
	// Todo 4.1b: Play one iteration of Game of Life
}

int main(int argc, char* argv[])
{
	Raster* raster = nullptr;

	// Todo 4.1a: Initialize random seed

	CommandLineParameter cmd(argc, argv);
	if (!cmd.patternFilename.empty())
	{
		raster = new Raster(cmd.patternFilename);
	}
	else
	{
		raster = new Raster(cmd.width, cmd.height, cmd.seedProbability);
	}

	for (int iteration = 0; iteration <= cmd.maxIterations; iteration++)
	{
		raster->save(cmd.outputDirectory + "game_of_life_" + std::to_string(iteration) + ".bmp");
		simulateInvasion(*raster, cmd.invasionFactor);
		simulateNextState(*raster, cmd.isTorus);
	}

	delete raster;

	return 0;
}
