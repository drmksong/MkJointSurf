#include "mesh.hpp"

mesh::mesh()
{
    this->surfData = NULL;
}

mesh::mesh(surf &surfData)
{
    this->surfData = surfData;
    setupMesh();
}

mesh::~mesh()
{
}

void mesh::setupMesh()
{
    if(this-surfData == NULL) {
        std::cout << "surfData is NULL" << std::endl;
        return; 
    }

    surf &surf_ = this->surfData;

    UnloadMesh(meshData); // TODO: check if this is safe to do...

    meshData.vertexCount = surf_.getSurfData().getSzX() * surf_.getSurfData().getSzY();
    meshData.triangleCount = (surf_.getSurfData().getSzX() - 1) * (surf_.getSurfData().getSzY() - 1) * 2;

    meshData.vertices = (float *)MemAlloc(meshData.vertexCount * 3 * sizeof(float));
    meshData.texcoords = (float *)MemAlloc(meshData.vertexCount * 2 * sizeof(float));
    meshData.normals = (float *)MemAlloc(meshData.vertexCount * 3 * sizeof(float));
    meshData.colors = (unsigned char *)MemAlloc(meshData.vertexCount * 4 * sizeof(unsigned char));
    meshData.indices = (unsigned short *)MemAlloc(meshData.triangleCount * 3 * sizeof(unsigned short));

    int vCounter = 0;
    int tcCounter = 0;
    int nCounter = 0;
    int cCounter = 0;
    int iCounter = 0;

    int szX = surf_.getSurfData().getSzX();
    int szY = surf_.getSurfData().getSzY();
    double maxValue = -1e10, minValue = 1e10;

    for (int j = 0; j < szY; j++)
    {
        for (int i = 0; i < szX; i++)
        {
            maxValue = std::max(maxValue, surf_(i, j));
            minValue = std::min(minValue, surf_(i, j));
        }
    }

    for (int j = 0; j < surf_.getSurfData().getSzY(); j++)
    // for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < surf_.getSurfData().getSzX(); i++)
        // for (int i = 0; i < 2; i++)
        {
            meshData.vertices[vCounter] = (float)(i - 50) / 10.0f;
            meshData.vertices[vCounter + 1] = (float)(j - 50) / 10.0f;
            meshData.vertices[vCounter + 2] = (float)surf_(i, j) / 100.0f + 1;
            if (j == 0)
                std::cout << std::format("i{:3},j{:3} : ({:3}({:3}), {:3}({:3}), {:3}({:3}) )", i, j, meshData.vertices[vCounter], vCounter, meshData.vertices[vCounter + 1], vCounter + 1, meshData.vertices[vCounter + 2], vCounter + 2) << std::endl;
            vCounter += 3;

            meshData.texcoords[tcCounter] = (float)i / 100.0f;
            meshData.texcoords[tcCounter + 1] = (float)j / 100.0f;
            tcCounter += 2;

            meshData.normals[nCounter] = 0.0f;
            meshData.normals[nCounter + 1] = 0.0f;
            meshData.normals[nCounter + 2] = 1.0f;
            nCounter += 3;

            meshData.colors[cCounter + 0] = int((surf_(i, j) - minValue) / (maxValue - minValue) * 255);
            meshData.colors[cCounter + 1] = 125;
            meshData.colors[cCounter + 2] = int((maxValue - surf_(i, j)) / (maxValue - minValue) * 255);
            meshData.colors[cCounter + 3] = 255;
            cCounter += 4;
        }
    }
    for (int j = 0; j < surf_.getSurfData().getSzY() - 1; j++)
        // for (int j = 0; j <  50; j++)
        for (int i = 0; i < surf_.getSurfData().getSzX() - 1; i++)
        // for (int i = 0; i < 1; i++)
        {
            {
                meshData.indices[iCounter] = (i)*surf_.getSurfData().getSzY() + (j);
                meshData.indices[iCounter + 2] = (i + 1) * surf_.getSurfData().getSzY() + (j);
                meshData.indices[iCounter + 1] = (i)*surf_.getSurfData().getSzY() + (j + 1);
                // if (i == 0)
                //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, meshData.indices[iCounter], meshData.indices[iCounter + 1], meshData.indices[iCounter + 2]) << std::endl;
                meshData.indices[iCounter + 3] = (i + 1) * surf_.getSurfData().getSzY() + (j);
                meshData.indices[iCounter + 5] = (i + 1) * surf_.getSurfData().getSzY() + (j + 1);
                meshData.indices[iCounter + 4] = (i)*surf_.getSurfData().getSzY() + (j + 1);
                // if (i == 0)
                //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, meshData.indices[iCounter + 3], meshData.indices[iCounter + 4], meshData.indices[iCounter + 5]) << std::endl;
            }
            iCounter += 6;
        }

    // for (int i = 0; i < surf_.getSurfData().getSzX() - 1; i++)
    // {
    //     for (int j = 0; j < surf_.getSurfData().getSzY() - 1; j++)
    //     {
    //         meshData.indices[iCounter] = (i)*surf_.getSurfData().getSzY() + (j);
    //         meshData.indices[iCounter + 1] = (i + 1) * surf_.getSurfData().getSzY() + (j + 1);
    //         meshData.indices[iCounter + 2] = (i)*surf_.getSurfData().getSzY() + (j + 1);
    //         // if (i == 0)
    //         //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, meshData.indices[iCounter], meshData.indices[iCounter + 1], meshData.indices[iCounter + 2]) << std::endl;
    //         meshData.indices[iCounter + 3] = (i)*surf_.getSurfData().getSzY() + (j);
    //         meshData.indices[iCounter + 4] = (i + 1) * surf_.getSurfData().getSzY() + (j);
    //         meshData.indices[iCounter + 5] = (i + 1) * surf_.getSurfData().getSzY() + (j + 1);
    //         // if (i == 0)
    //         //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, meshData.indices[iCounter + 3], meshData.indices[iCounter + 4], meshData.indices[iCounter + 5]) << std::endl;
    //     }
    //     iCounter += 6;
    // }

    UploadMesh(&meshData, false);

}

bool mesh::update(surf &surfData)
{
    this->surfData = surfData;
    setupMesh();

    return true;
}

void mesh::draw()
{
    // DrawMesh(mesh, position, rotation, color);
    return;
}

double & mesh::operator()(int i, int j)
{
    return this->surfData(i, j);
}

void mesh::log()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            std::cout << this->surfData(i, j) << std::endl;
    return;
}