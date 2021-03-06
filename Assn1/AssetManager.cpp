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
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<vec3> facenorms;

	std::vector<vec3> tangents;
	std::vector<vec3> bitangents;
	std::map<std::string, GModel*> dict;
	std::map<std::string, GLuint, GLuint> ndict;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<vec3> temp_vertices;
	std::vector<vec2> temp_uvs;
	std::vector<vec3> temp_normals;
	std::string old_groupname;
	char* filename = new char[name_file.size() + 1];
	strcpy_s(filename, name_file.size() + 1, name_file.c_str());

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
			std::tuple<GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,vec3,vec3,int> indexes;
			double maxx = 0, maxy = 0, maxz = 0;
			double minx = 0, miny = 0, minz = 0;
			double width, height, depth;
			// For each vertex of each triangle
			for (unsigned int i = 0; i<vertexIndices.size(); i++) {
				unsigned int vertexIndex = vertexIndices[i];
				unsigned int uvIndex = uvIndices[i];
				unsigned int normalIndex = normalIndices[i];
				vec3 vertex = temp_vertices[vertexIndex - 1];
				vec2 uv = temp_uvs[uvIndex - 1];
				vec3 normal = temp_normals[normalIndex - 1];
				vertices.push_back(vertex);
				uvs.push_back(uv);
				normals.push_back(normal);
			}
			//tangent vector calculation
			for (unsigned int i = 0; i < vertices.size(); i = i + 3) {
				// Shortcuts for vertices
				vec3 & v0 = vertices[i + 0];
				vec3 & v1 = vertices[i + 1];
				vec3 & v2 = vertices[i + 2];

				// Shortcuts for UVs
				vec2 & uv0 = uvs[i + 0];
				vec2 & uv1 = uvs[i + 1];
				vec2 & uv2 = uvs[i + 2];

				// Edges of the triangle : postion delta
				vec3 deltaPos1 = v1 - v0;
				vec3 deltaPos2 = v2 - v0;

				// UV delta
				vec2 deltaUV1 = uv1 - uv0;
				vec2 deltaUV2 = uv2 - uv0;

				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
				vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

				// Set the same tangent for all three vertices of the triangle.
				// They will be merged later, in vboindexer.cpp
				tangents.push_back(tangent);
				tangents.push_back(tangent);
				tangents.push_back(tangent);

				// Same thing for binormals
				bitangents.push_back(bitangent);
				bitangents.push_back(bitangent);
				bitangents.push_back(bitangent);
			}
			//facenormal calculation
			for (unsigned int i = 0; i < normals.size(); i = i + 3)
			{
				vec3 facenorm = cross(vertices[i + 1] - vertices[i], vertices[i + 2] - vertices[i]);
				facenorms.push_back(facenorm);
				facenorms.push_back(facenorm);
				facenorms.push_back(facenorm);
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
			GLuint uv_buf;
			GLuint normal_buf;
			GLuint face_buf;
			GLuint tan_buf;
			GLuint bitan_buf;
			int siz = sizeof(vec3) * vertices.size() + sizeof(vec2) * uvs.size() + sizeof(vec3) * normals.size() + sizeof(vec3) * facenorms.size();
			int wowmuchsize = sizeof(vec3);
			glGenBuffers(1, &groupint);
			glGenBuffers(1, &uv_buf);
			glGenBuffers(1, &normal_buf);
			glGenBuffers(1, &face_buf);
			glGenBuffers(1, &tan_buf);
			glGenBuffers(1, &bitan_buf);

			glBindBuffer(GL_ARRAY_BUFFER, groupint);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, uv_buf);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * uvs.size(), &uvs[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, normal_buf);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, face_buf);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * facenorms.size(), &facenorms[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, tan_buf);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * tangents.size(), &tangents[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, bitan_buf);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * bitangents.size(), &bitangents[0], GL_STATIC_DRAW);

			indexes = std::make_tuple(groupint, uv_buf, normal_buf, face_buf, tan_buf, bitan_buf,
				vec3((minx + maxx) / 2, (miny + maxy) / 2, (minz + maxz) / 2), vec3(width, height, depth), vertices.size());
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
		else if (strcmp(lineHeader, "vt") == 0)
		{
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "g") == 0) {
			char groupname[128];
			std::tuple<GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,vec3,vec3,int> indexes;
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
					unsigned int uvIndex = uvIndices[i];
					unsigned int normalIndex = normalIndices[i];
					vec3 vertex = temp_vertices[vertexIndex - 1];
					vec2 uv = temp_uvs[uvIndex - 1];
					vec3 normal = temp_normals[normalIndex - 1];
					vertices.push_back(vertex);
					uvs.push_back(uv);
					normals.push_back(normal);
				}
				//tangent vector calculation
				for (unsigned int i = 0; i < vertices.size(); i = i + 3) {
					// Shortcuts for vertices
					vec3 & v0 = vertices[i + 0];
					vec3 & v1 = vertices[i + 1];
					vec3 & v2 = vertices[i + 2];

					// Shortcuts for UVs
					vec2 & uv0 = uvs[i + 0];
					vec2 & uv1 = uvs[i + 1];
					vec2 & uv2 = uvs[i + 2];

					// Edges of the triangle : postion delta
					vec3 deltaPos1 = v1 - v0;
					vec3 deltaPos2 = v2 - v0;

					// UV delta
					vec2 deltaUV1 = uv1 - uv0;
					vec2 deltaUV2 = uv2 - uv0;

					float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
					vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
					vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

					// Set the same tangent for all three vertices of the triangle.
					tangents.push_back(tangent);
					tangents.push_back(tangent);
					tangents.push_back(tangent);

					// Same thing for binormals
					bitangents.push_back(bitangent);
					bitangents.push_back(bitangent);
					bitangents.push_back(bitangent);
				}

				for (unsigned int i = 0; i < normals.size(); i = i + 3)
				{
					vec3 facenorm = cross(vertices[i + 1] - vertices[i], vertices[i + 2] - vertices[i]);
					facenorms.push_back(facenorm);
					facenorms.push_back(facenorm);
					facenorms.push_back(facenorm);
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
				GLuint uv_buf;
				GLuint normal_buf;
				GLuint face_buf;
				GLuint tan_buf;
				GLuint bitan_buf;
				int siz = sizeof(vec3) * vertices.size() + sizeof(vec2) * uvs.size() + sizeof(vec3) * normals.size() + sizeof(vec3) * facenorms.size();
				int wowmuchsize = sizeof(vec3);
				glGenBuffers(1, &groupint);
				glGenBuffers(1, &uv_buf);
				glGenBuffers(1, &normal_buf);
				glGenBuffers(1, &face_buf);
				glGenBuffers(1, &tan_buf);
				glGenBuffers(1, &bitan_buf);

				glBindBuffer(GL_ARRAY_BUFFER, groupint);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, uv_buf);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * uvs.size(), &uvs[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, normal_buf);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, face_buf);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * facenorms.size(), &facenorms[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, tan_buf);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * tangents.size(), &tangents[0], GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, bitan_buf);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * bitangents.size(), &bitangents[0], GL_STATIC_DRAW);

				indexes = std::make_tuple(groupint, uv_buf, normal_buf, face_buf, tan_buf, bitan_buf,
					vec3((minx + maxx) / 2, (miny + maxy) / 2, (minz + maxz) / 2), vec3(width, height, depth), vertices.size());
				dict[old_groupname] = new GModel(indexes);;
				std::string groupnametmp = groupname;
				vertexIndices.clear();
				uvIndices.clear();
				normalIndices.clear();
				vertices.clear();
				uvs.clear();
				normals.clear();
				facenorms.clear();
				tangents.clear();
				bitangents.clear();
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
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
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
