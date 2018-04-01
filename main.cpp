#include <vector>
#include <iostream>
#include "UMap.h"

typedef std::vector<float>        vector_float;
typedef std::vector<vector_float> vector2d_float;

int main()
{
    UMap umap;

    // Examples for storing
    umap["myInteger"] = 42;
    umap["myFloat"]   = 22.5f;
    umap["myDouble"]  = 558.2390183;
    umap["myString"]  = std::string("la dee dah");  // Doesn't fair well with char* at the moment

    vector_float   v1;
    vector2d_float v2;
    for (float i=0.0f; i<10.0f; i+=0.7f)
    {
        vector_float temp;
        for (float j=0.0f; j<7.0f; j+=0.33f)
        {
            temp.push_back(j-i);
        }
        v1.push_back(i);
        v2.push_back(temp);
    }

    umap["my1dvector"] = v1;
    umap["my2dvector"] = v2;

    // Examples for retrieving
    std::cout << "myInteger: " << umap["myInteger"].as<int>()         << std::endl;
    std::cout << "myFloat: "   << umap["myFloat"].as<float>()         << std::endl;
    std::cout << "myDouble: "  << umap["myDouble"].as<double>()       << std::endl;
    std::cout << "myString: "  << umap["myString"].as<std::string>()  << std::endl;

    auto v1new = umap["my1dvector"].as<vector_float>();
    auto v2new = umap["my2dvector"].as<vector2d_float>();

    std::cout << "my1dvector: ";
    for (auto entry : v1new) 
        std::cout << entry << " ";
    std::cout << std::endl << std::endl;

    std::cout << "my2dvector: " << std::endl;
    for (auto ventry : v2new)
    {
        for (auto entry : ventry)
        {
            std::cout << entry << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // If you are unsure if there is an entry...
    std::cout << "bogus number: " << umap["bogus"].as<int>(-1) << std::endl;

    return 0;
}