#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "amazing/objects/Items.h"
#include "amazing/objects/Discounts.h"
#include "amazing/objects/Orders.h"
#include "amazing/objects/ProcessedOrders.h"
#include "amazing/file_reader/CsvReader.h"

// argv[1] shall be path to the items CSV
// argv[2] shall be path to the discounts CSV
int main(int argc, char* argv[])
{
	std::shared_ptr<CsvReader> csv_reader(new CsvReader);
	std::ofstream txt_writer;

	Items items;
	Discounts discounts;
	const std::vector<IObjects*> initial_objects = {&items, &discounts};

	Orders orders;
	ProcessedOrders processed_orders;
	std::string filename;

	// test
	//const std::vector<const char*> input_args = { "items.csv", "discount.csv" };

	int i = 1;
	for (IObjects* object : initial_objects)
	{
		if (i < argc)
		{
			// take app argument
			filename = argv[i];
		}
		else
		{
			// read command line input if there is no proper argument
			std::cout << "Enter " << object->getObjectType() << " CSV file: ";
			std::cin >> filename;

			// test
			//filename = input_args[i - 1];
		}
		i++;

		try
		{
			// open file
			csv_reader->open(filename);

			// deserialize
			(*object) << csv_reader;

			// report success
			std::cout << "Succesfully processed " << object->getObjectType() << " data." << std::endl;
		}
		catch (const std::exception& e)
		{
			// report error & exit
			std::cerr << object->getObjectType() << " read failed -> " << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	}

	// endless loop for entering the orders
	// enter "exit" in order to break the loop
	while (true)
	{
		// get the order CSV file
		std::cout << "Enter " << orders.getObjectType() << " CSV file: ";
		std::cin >> filename;
		if (filename == "exit")
		{
			std::cout << "Exit the app.\n";
			break;
		}

		try
		{
			// open file
			csv_reader->open(filename);

			// deserialize
			orders << csv_reader;

			// report success
			std::cout << "Succesfully processed " << orders.getObjectType() << " data." << std::endl;

			// generate processed_orders
			processed_orders.processOrder(&orders, &items, &discounts);

			filename = "processed_" + filename.substr(0, filename.find(".csv")) + ".txt";
			txt_writer.open(filename);

			// write processed_orders
			processed_orders >> txt_writer;

			txt_writer.close();

			// report success
			std::cout << "Successfully written " << processed_orders.getObjectType() << " data into " << filename << std::endl;
		}
		catch (const std::exception& e)
		{
			// report error & exit
			std::cerr << orders.getObjectType() << " read failed -> " << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}