#include "MkMesh.hpp"

MkMesh::MkMesh()
{
    meshData = {0};
    surfData.Init();
}

MkMesh::MkMesh(MkSurf &surfData)
{
    this->surfData = surfData;
    SetupMesh();
}

MkMesh::~MkMesh()
{
    UnloadMesh(meshData); // TODO: check if this is safe to do...
}

void MkMesh::SetupMesh()
{
    if (this->surfData.GetSurfData().getSzX() == 0 || this->surfData.GetSurfData().getSzY() == 0)
    {
        std::cout << "surfData is NULL" << std::endl;
        return;
    }

    MkSurf &surf_ = this->surfData;

    int szX = surf_.GetSurfData().getSzX();
    int szY = surf_.GetSurfData().getSzY();
    std::cout << std::format("szX: {:3}, szY: {:3}", szX, szY) << std::endl;

    UnloadMesh(meshData); // TODO: check if this is safe to do...

    meshData.vertexCount = szX * szY;
    meshData.triangleCount = (szX - 1) * (szY - 1) * 2;

    meshData.vertices = (float *)MemAlloc(meshData.vertexCount * 3 * sizeof(float));
    meshData.texcoords = (float *)MemAlloc(meshData.vertexCount * 2 * sizeof(float));
    meshData.normals = (float *)MemAlloc(meshData.vertexCount * 3 * sizeof(float));
    meshData.colors = (unsigned char *)MemAlloc(meshData.vertexCount * 4 * sizeof(unsigned char));
    meshData.indices = (unsigned short *)MemAlloc(meshData.triangleCount * 3 * sizeof(unsigned short));

    if (meshData.vertices == NULL || meshData.texcoords == NULL || meshData.normals == NULL ||
        meshData.colors == NULL || meshData.indices == NULL)
    {
        std::cout << "Mesh allocation failed" << std::endl;
        exit(1);
    }

    int vCounter = 0;
    int tcCounter = 0;
    int nCounter = 0;
    int cCounter = 0;
    int iCounter = 0;

    double maxValue = -1e10, minValue = 1e10;

    for (int j = 0; j < szY; j++)
    {
        for (int i = 0; i < szX; i++)
        {
            maxValue = std::max(maxValue, surf_(i, j));
            minValue = std::min(minValue, surf_(i, j));
        }
    }

    std::cout << "setup loc 1" << std::endl;

    for (int j = 0; j < szY; j++)
    {
        for (int i = 0; i < szX; i++)
        {
            meshData.vertices[vCounter] = (float)(i - 50) / 10.0f;
            meshData.vertices[vCounter + 1] = (float)(j - 50) / 10.0f;
            meshData.vertices[vCounter + 2] = (float)surf_(i, j) / 50.0f;
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

    std::cout << "setup loc 2 " << std::endl;
    for (int j = 0; j < szY - 1; j++)
    {
        for (int i = 0; i < szX - 1; i++)
        {
            {
                meshData.indices[iCounter] = (i)*szY + (j);
                meshData.indices[iCounter + 2] = (i + 1) * szY + (j);
                meshData.indices[iCounter + 1] = (i)*szY + (j + 1);
                // if (i == 0)
                //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, meshData.indices[iCounter], meshData.indices[iCounter + 1], meshData.indices[iCounter + 2]) << std::endl;
                meshData.indices[iCounter + 3] = (i + 1) * szY + (j);
                meshData.indices[iCounter + 5] = (i + 1) * szY + (j + 1);
                meshData.indices[iCounter + 4] = (i)*szY + (j + 1);
                // if (i == 0)
                //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, meshData.indices[iCounter + 3], meshData.indices[iCounter + 4], meshData.indices[iCounter + 5]) << std::endl;
            }
            iCounter += 6;
        }
    }

    std::cout << std::format("vCounter:{}, tcCounter:{}, nCounter:{}, cCounter:{}, iCounter:{}", vCounter, tcCounter, nCounter, cCounter, iCounter) << std::endl;
    std::cout << "setup loc 3" << std::endl;
    UploadMesh(&meshData, false);
    std::cout << "setup loc 4" << std::endl;
}

bool MkMesh::Update(MkSurf &surfData)
{
    this->surfData = surfData;
    SetupMesh();

    return true; // check if surfData is valid
}

bool MkMesh::Update()
{
    SetupMesh();

    return true; // check if surfData is valid
}

void MkMesh::Draw()
{
    // DrawMesh(MkMesh, position, rotation, color);
    return;
}

double &MkMesh::operator()(int i, int j)
{
    return this->surfData(i, j);
}

void MkMesh::Log()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            std::cout << this->surfData(i, j) << std::endl;
    return;
}