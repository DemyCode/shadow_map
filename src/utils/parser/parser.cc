//
// Created by mehdi on 28/02/2020.
//

#include "parser.hh"

Parser::Parser(std::string path) {
    std::cout << "Parsing : " << path << std::endl;
    std::ifstream file(path);
    if (!file.is_open())
        std::cerr << "File not found" << std::endl;
    size_t countline = 0;
    std::string regdouble = "[+-]?([0-9]*[.])?[0-9]+";
    for (std::string line; std::getline(file, line); )
    {
        std::cout << "Treating line : " << countline << std::endl;
        countline++;
        std::smatch smatch;
        const std::regex regex("#.*");
        if (std::regex_search(line, smatch, regex))
            continue;
        const std::regex regex2("v[ \t]+([+-]?([0-9]*[.])?[0-9]+)[ \t]+([+-]?([0-9]*[.])?[0-9]+)[ \t]+([+-]?([0-9]*[.])?[0-9]+)");
        if (std::regex_search(line, smatch, regex2))
        {
            std::string f1 = smatch[1];
            this->vertices_.push_back(std::stod(smatch[1]));
            this->vertices_.push_back(std::stod(smatch[3]));
            this->vertices_.push_back(std::stod(smatch[5]));
            continue;
        }
        const std::regex regex3("vn[ \t]+([+-]?([0-9]*[.])?[0-9]+)[ \t]+([+-]?([0-9]*[.])?[0-9]+)[ \t]+([+-]?([0-9]*[.])?[0-9]+)");
        if (std::regex_search(line, smatch, regex3))
        {
            std::string f1 = smatch[1];
            this->normals_.emplace_back(std::stod(smatch[1]), std::stod(smatch[3]), std::stod(smatch[5]));
            continue;
        }
        const std::regex regex4("f[ \t]+([0-9]+)/?([0-9]*)/?([0-9]*)[ \t]+([0-9]+)/?([0-9]*)/?([0-9]*)[ \t]+([0-9]+)/?([0-9]*)/?([0-9]*)");
        if (std::regex_search(line, smatch, regex4))
        {
            // GO FOR INDICE 1 4 et 7
            indices_.push_back(std::stoi(smatch[1]));
            indices_.push_back(std::stoi(smatch[4]));
            indices_.push_back(std::stoi(smatch[7]));
        }
    }
}