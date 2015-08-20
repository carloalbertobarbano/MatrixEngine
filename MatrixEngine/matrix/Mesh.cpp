#include "Mesh.h"

void MeshSection::ConstructVAO()
{
	int vertex_location = 0;
	int normal_location = 1;
	int texture_location = 2;
	int tangent_location = 3;

	vao.Construct(3);
	vao.BufferData(0, GL_ARRAY_BUFFER, vert.size()*sizeof(float), &vert[0], GL_STATIC_DRAW);
	vao.VertexAttribute(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if (norm.size() > 0)
	{
		vao.BufferData(1, GL_ARRAY_BUFFER, norm.size()*sizeof(float), &norm[0], GL_STATIC_DRAW);
		vao.VertexAttribute(normal_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}


	if (tex_coord.size() > 0)
	{
		vao.BufferData(2, GL_ARRAY_BUFFER, tex_coord.size()*sizeof(float), &tex_coord[0], GL_STATIC_DRAW);
		vao.VertexAttribute(texture_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (tang.size() > 0)
	{
		vao.BufferData(3, GL_ARRAY_BUFFER, tang.size()*sizeof(float), &tang[0], GL_STATIC_DRAW);
		vao.VertexAttribute(tangent_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	vao.unbind();
}

void MeshSection::Render()
{
	vao.DrawArrays(GL_TRIANGLES, 0, vert.size(), &indices[0]);
}

Mesh::Mesh(){

}

Mesh::~Mesh() {
    cout << "Deleting mesh " << endl;
}

void Mesh::LoadFromFile(string file) {
	cout << "Loading " << file << ".." << endl;

	Importer importer;
	const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		WriteOnStream("Could not load file " + file, error_stream);
		return;
	}



	processNode(scene->mRootNode, scene);

	cout << "Mesh " << file << " loaded. " << endl;
}

void Mesh::processNode(aiNode *node, const aiScene *scene) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}


	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

void Mesh::processMesh(aiMesh *mesh, const aiScene *scene) {
	MeshSection section;

	for (int i = 0; i < mesh->mNumVertices; i++) {
		vec3 vert(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vec3 norm(mesh->mNormals[i].x,  mesh->mNormals[i].y,  mesh->mNormals[i].z);
		//vec3 tang(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
		//vec2 tex_coord(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		vec3 tang(0, 0, 0);
		vec2 tex_coord(0, 0);

		section.vert.push_back(vert);
		section.norm.push_back(norm);
		section.tang.push_back(tang);
		section.tex_coord.push_back(tex_coord);
	}

	//MeshSection ordered_section;

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++) {
			section.indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
	aiColor4D ambient, diffuse, specular;
	float shininess;

	aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT,  &ambient);
	aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE,  &diffuse);
	aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &specular);
	aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &shininess);

	Material material;
	material.ambient  = vec4(ambient.r, ambient.g, ambient.b, ambient.a);
	material.diffuse  = vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	material.specular = vec4(specular.r, specular.g, specular.b, specular.a);
	material.shininess = shininess;
	section.material = material;

	for (int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++) {
		aiString name;
		mat->GetTexture(aiTextureType_DIFFUSE, i, &name);

		section.material.texture_diffuse.load_from_file(name.C_Str());
	}

	section.ConstructVAO();

	this->sections.push_back(section);
}
