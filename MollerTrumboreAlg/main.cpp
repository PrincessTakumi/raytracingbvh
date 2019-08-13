#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

#include "vec3.h"
#include "algorithm.h"
#include "camera.h"
#include "material.h"
#include "ray.h"
#include "octree.h"
#include "BVH.h"
#include "mesh2.h"

using namespace std;

vec3 getcolor(const Ray &r, BVH *tree, int depth)
{
	vector<Triangle*> list;
	tree->hit(r, list);
	if (list.size() == 0)
	{
		vec3 dir = (r.direction()).unit_vector();
		float t = 0.5 * (dir.e[1] + 1.0);
		return vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
	}

	hit_record rec;
	bool hit = false;
	float tempmax = numeric_limits<float>::max();
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i)->hit(r, 1e-3, tempmax, rec))
		{
			hit = true;
			tempmax = rec.t;
		}
	}

	if (hit)
	{
		Ray scatter;
		vec3 attenuation;
		if (depth < 10 && (rec.mat)->scatter(r, rec, attenuation, scatter))
			return attenuation * getcolor(scatter, tree, depth + 1);
		else
			return vec3(0, 0, 0);
	}
	else
	{
		vec3 dir = (r.direction()).unit_vector();
		float t = 0.5 * (dir.e[1] + 1.0);
		return vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
	}
}

int main(int argc, char **argv)
{

	srand(time(NULL));

	ofstream myfile;
	myfile.open("../reventondebugtest.ppm");

	int start_time = clock();

	int width = 1920;
	int height = 1080;
	int ns = 2;

	myfile << "P3\n" << width << " " << height << "\n255\n";

	vector<Mesh*> meshes;
	meshes.push_back(new Mesh("obj/monkey.obj", vec3(0, 0, 0)));
	//meshes.push_back(new Mesh("obj/rev_glass.obj", vec3(225, 0, 0)));
	//meshes.push_back(new Mesh("obj/monkey.obj", vec3(-3, 0, -0.5)));
	//meshes.push_back(new Mesh("obj/.obj", vec3(x, y, z)));

	vector<Triangle*> triList;
	for (int i = 0; i < meshes.size(); i++)
	{
		for (int j = 0; j < meshes.at(i)->triangles.size(); j++)
			triList.push_back(meshes.at(i)->triangles.at(j));
	}

	BVH *root = new BVH(triList, 0);

	vec3 lookfrom(0, 1, 6);
	vec3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	float dist_to = (lookfrom - lookat).length();
	float aperture = 0;
	Camera cam(lookfrom, lookat, vup, 45, float(width) / float(height), aperture, dist_to);

	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			vec3 color(0, 0, 0);
			for (int k = 0; k < ns; k++)
			{
				float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(width);
				float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(height);
				Ray r = cam.get_ray(u, v);
				color += getcolor(r, root, 0);
			}

			color /= float(ns);


			color = vec3(pow(color.e[0], 1.0 / 2.2),
				pow(color.e[1], 1.0 / 2.2),
				pow(color.e[2], 1.0 / 2.2));

			myfile << int(255.99*color.e[0]) << " " << int(255.99*color.e[1]) << " " << int(255.99*color.e[2]) << "\n";
		}
	}

	myfile.close();

	int stop_time = clock();

	cout << ">> Run time : " << (stop_time - start_time) / 1000.0 << endl;
	cout << ">> Triangles : " << triList.size() << endl;

	cin.get();

	return 0;

};