#include "AssetManager.h"
#include "mat.h"
#include <vector>
#include <algorithm>

void AssetManager::loadModelFromFile(std::string name_file)
{
	//TODO : implement model loading from given .wobj file.  
	//this function
	//1. parses .wobj
	//2. put the vertex data into VBO (according to group. Separately.)
	//3. finds the best boundbox according to vertices
	//4. returns map from GROUP NAME(specified in .wobj) to (VBO index, boundbox_width, boudbox_height)
	//		string -> (GLuint, double, double)
	//IT IS A STATIC FUNCTION!!!! IT CANNOT USE "this"
	//USED ONLY FROM CLASS DIRECTLY

	std::vector<vec3> vertices;
	std::map<std::string, GModel*> dict;
	std::vector<unsigned int> vertexIndices;
	std::vector<vec3> temp_vertices;
	std::string old_groupname;
	char* filename = new char[name_file.size() + 1];
	strcpy_s(filename, name_file.size() + 1, name_file.c_str());

	int verticesize = 0;

	FILE * file = fopen(filename, "r");
	if (file == nullptr) {
		std::cerr << "Invalid location or filename : " << filename << std::endl;
		system("pause");
		exit(1);
	}
	delete filename;
	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			std::tuple<GLuint, vec3, vec3, int> indexes;
			double maxx = 0, maxy = 0, maxz = 0;
			double minx = 0, miny = 0, minz = 0;
			double width, height, depth;
			// For each vertex of each triangle
			for (unsigned int i = 0; i<vertexIndices.size(); i++) {
				unsigned int vertexIndex = vertexIndices[i];
				vec3 vertex = temp_vertices[vertexIndex - 1];
				vertices.push_back(vertex);
			}

			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices[i].x > maxx) maxx = vertices[i].x;
				if (vertices[i].y > maxy) maxy = vertices[i].y;
				if (vertices[i].z > maxz) maxz = vertices[i].z;
				if (vertices[i].x < minx) minx = vertices[i].x;
				if (vertices[i].y < miny) miny = vertices[i].y;
				if (vertices[i].z < minz) minz = vertices[i].z;
			}

			width = maxx - minx;
			height = maxy - miny;
			depth = maxz - minz;

			//wow. make the bound box placed on 0,0,0
			for (std::vector<vec3>::iterator it = vertices.begin(); it != vertices.end(); it++) {
				(*it) = (*it) - vec3((minx + maxx) / 2, (miny + maxy) / 2, (minz + maxz) / 2);
			}

			GLuint groupint;
			glGenBuffers(1, &groupint);
			glBindBuffer(GL_ARRAY_BUFFER, groupint);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

			indexes = std::make_tuple(groupint, vec3((minx+maxx)/2, (miny+maxy)/2, (minz+maxz)/2), vec3(width, height, depth), vertices.size());
			dict[old_groupname] = new GModel(indexes);
			break;
		}

		// EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "g") == 0) {
			char groupname[128];
			std::tuple<GLuint, vec3, vec3, int> indexes;
			double maxx = 0, maxy = 0, maxz = 0;
			double minx = 0, miny = 0, minz = 0;
			double width, height, depth;
			fscanf(file, "%s\n", groupname);
			std::string groupnametmp = groupname;
			if (old_groupname.size() != 0)
			{
				// For each vertex of each triangle
				for (unsigned int i = 0; i<vertexIndices.size(); i++) {
					unsigned int vertexIndex = vertexIndices[i];
					vec3 vertex = temp_vertices[vertexIndex - 1];
					vertices.push_back(vertex);
				}

				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices[i].x > maxx) maxx = vertices[i].x;
					if (vertices[i].y > maxy) maxy = vertices[i].y;
					if (vertices[i].z > maxz) maxz = vertices[i].z;
					if (vertices[i].x < minx) minx = vertices[i].x;
					if (vertices[i].y < miny) miny = vertices[i].y;
					if (vertices[i].z < minz) minz = vertices[i].z;
				}

				width = maxx - minx;
				height = maxy - miny;
				depth = maxz - minz;

				for (std::vector<vec3>::iterator it = vertices.begin(); it != vertices.end(); it++) {
					(*it) = (*it) - vec3((minx + maxx) / 2, (miny + maxy) / 2, (minz + maxz) / 2);
				}

				GLuint groupint;
				glGenBuffers(1, &groupint);
				glBindBuffer(GL_ARRAY_BUFFER, groupint);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

				indexes = std::make_tuple(groupint, vec3((minx + maxx) / 2, (miny + maxy) / 2, (minz + maxz) / 2), vec3(width, height, depth), vertices.size());
				dict[old_groupname] = new GModel(indexes);
				std::string groupnametmp = groupname;
				vertexIndices.clear();
				vertices.clear();
			}
			old_groupname = groupname;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			verticesize += 3;
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	this->data_models.insert(dict.begin(), dict.end());
}

void AssetManager::loadTextureFromFile(std::string name_group, GModel::TextureType type, std::string name_file) 
{
	try {
		data_models.at(name_group)->setTexture(type, name_file);
	}
	catch (...) {
		std::cerr << "Tried to set Texture for group " << name_group << " but failed" << std::endl;
	}
}

GModel* AssetManager::getModel(std::string name_group)
{
	try {
		return data_models.at(name_group);
	}
	catch (...) {
		std::cerr << "model data doesn't exist : " << name_group << std::endl;
		return nullptr;
	}
}

vec3 AssetManager::getGlobalPos(std::string name_group)
{
	try {
		return data_models.at(name_group)->getPos();
	}
	catch (...) {
		std::cerr << "model data doesn't exist : " << name_group << std::endl;
		return vec3();
	}
}

vec3 AssetManager::getRelativePos(std::string child, std::string parent)
{
	try {
		vec3 pos_c = data_models.at(child)->getPos();
		vec3 pos_p = data_models.at(parent)->getPos();
		return pos_c - pos_p;
	}
	catch (...) {
		std::cerr << "model data doesn't exist : " << child << ", " << parent << std::endl;
		return vec3();
	}
}

AssetManager::~AssetManager() {
	GLuint* buffer = (GLuint*)malloc(sizeof(GLuint)*data_models.size());
	int i = 0;
	for (std::map<std::string, GModel*>::iterator it = data_models.begin();
	it != data_models.end(); it++) {
		buffer[i++] = (*it).second->getModelID();
		delete (*it).second;
	}
	glDeleteBuffers(data_models.size(), buffer);
	delete buffer;
}