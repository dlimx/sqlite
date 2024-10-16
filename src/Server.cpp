#include <cstring>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string database_file_path = argv[1];
    std::string command = argv[2];

    if (command == ".dbinfo") {
        std::ifstream database_file(database_file_path, std::ios::binary);
        if (!database_file) {
            std::cerr << "Failed to open the database file" << std::endl;
            return 1;
        }

        // Uncomment this to pass the first stage
        database_file.seekg(16);  // Skip the first 16 bytes of the header
        
        char page_buffer[2];
        database_file.read(page_buffer, 2);
        
        unsigned short page_size = (static_cast<unsigned char>(page_buffer[1]) | (static_cast<unsigned char>(page_buffer[0]) << 8));

        database_file.seekg(103);  // Skip the first 28 bytes of the header
        
        char table_buffer[2];
        database_file.read(table_buffer, 2);

        unsigned int table_count = (static_cast<unsigned char>(table_buffer[1]) | (static_cast<unsigned char>(table_buffer[0]) << 8));
        
        std::cout << "database page size: " << page_size << std::endl;
        std::cout << "number of tables: " << table_count << std::endl;
    }

    return 0;
}
