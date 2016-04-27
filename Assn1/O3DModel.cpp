#include "O3DModel.h"
#include <vector>

O3DModel::O3DModel(double x, double y, double z, RotPoint rotcnt, double rotx, double roty, std::string type, std::tuple<GLuint,double,double,double,int> data_model)
	:GObject(Rect(0, 0, 0, 0), Rect(0, 0, 0, 0), type)
{
	//inits model... just as ORect
}

std::map<std::string, std::tuple<GLuint,double,double,double,int>> O3DModel::loadModelFromFile(std::string name_file) { 
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
	std::map<std::string, std::tuple<GLuint, double, double, double, int>> dict;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<vec3> temp_vertices;
	std::vector<vec2> temp_uvs;
	std::vector<vec3> temp_normals;
	char* filename = new char[sizeof(name_file) + 1];
	strcpy_s(filename, name_file.size() + 1, name_file.c_str());
	delete filename;

	int verticesize = 0;

	FILE * file = fopen(filename, "r");
	while (1) 
	{
		char lineHeader[128];
		// read the first word of the line
		std::string old_groupname;
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			std::tuple<GLuint, double, double, double, int> indexes;
			vec3* arrvert;
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

			arrvert = &vertices[0];

			GLuint groupint;
			glGenBuffers(1, &groupint);
			glBindBuffer(GL_ARRAY_BUFFER, groupint);
			glBufferData(GL_ARRAY_BUFFER, sizeof(arrvert), arrvert, GL_STATIC_DRAW);

			indexes = std::make_tuple(groupint, width, height, depth, vertices.size());
			dict[old_groupname] = indexes;
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
			std::string groupname;
			std::tuple<GLuint, double, double, double, int> indexes;
			vec3* arrvert;
			double maxx = 0, maxy = 0, maxz = 0;
			double minx = 0, miny = 0, minz = 0;
			double width, height, depth;
			fscanf(file, "%s\n", groupname);		
			if(old_groupname.size() != 0)
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

				arrvert = &vertices[0];

				GLuint groupint;
				glGenBuffers(1, &groupint);
				glBindBuffer(GL_ARRAY_BUFFER, groupint);
				glBufferData(GL_ARRAY_BUFFER, sizeof(arrvert), arrvert, GL_STATIC_DRAW);

				indexes = std::make_tuple(groupint, width, height, depth, vertices.size());
				dict[old_groupname] = indexes;
				old_groupname = groupname;
				vertexIndices.clear();
				vertices.clear();
			}
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
	return dict;
}

void O3DModel::draw(mat4 MVMatrix) {
	//TODO : implement drawing the 3d model
}

void O3DModel::frameAction() {

}