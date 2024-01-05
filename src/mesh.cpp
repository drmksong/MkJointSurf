#include "mesh.hpp"

mesh::mesh()
{
    setupMesh();
}

mesh::mesh(MkPoints &vertices)
{
    this->vertices = vertices;
    setupMesh();
}

mesh::~mesh()
{
}

void mesh::setupMesh()
{

    if (this->vertices.GetSize() == 0)
    {
        std::cout << "Default mesh will be used instead. " << std::endl;
        this->vertices.Initialize(10000);
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            this->vertices[i * 100 + j].X = i;
            this->vertices[i * 100 + j].Y = j;
            this->vertices[i * 100 + j].Z = 0;
        }
    }
}

bool mesh::update(surf &surfData)
{

    return true;
}

void mesh::draw()
{
    // DrawMesh(mesh, position, rotation, color);
    return;
}

double & mesh::operator()(int i, int j)
{
    return this->vertices[i * 100 + j].Z;
}

void mesh::log()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            std::cout << this->vertices[i * 100 + j].X << " " << this->vertices[i * 100 + j].Y << " " << this->vertices[i * 100 + j].Z << " " << std::endl;
    return;
}