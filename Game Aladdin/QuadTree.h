//#pragma once
//#include "Object.h"
//
//class QTNode {
//public:
//	QTNode(long left, long top, long right, long bottom);
//	//QTNode* parent;
//	QTNode* childrens[4] = { nullptr };
//	long left, top, right, bottom;
//	std::vector<LPOBJECT> objects;
//	~QTNode();
//};
//
//class QuadTree
//{
//private:
//	D3DXVECTOR2 mapSize;
//	D3DXVECTOR2 cameraSize;
//	std::vector<LPOBJECT> objects;
//	QTNode* root;
//
//	void Build(QTNode*& node);
//	void GetObjects(QTNode* root, LPCAMERA camera, std::vector<LPOBJECT> &ObjectsInView);
//	bool CheckNodeSize(QTNode* node);
//
//public:
//	QuadTree();
//	void Init(D3DXVECTOR2 camSize, D3DXVECTOR2 mapSize, std::vector<LPOBJECT> listObj);
//	std::vector<LPOBJECT> GetObjectsInCamera(LPCAMERA camera);
//	~QuadTree();
//};
//
//typedef QuadTree* LPQUADTREE;
//
