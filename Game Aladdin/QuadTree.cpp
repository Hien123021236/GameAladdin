//#include <set>
//
//#include "QuadTree.h"
//
//QuadTree::QuadTree()
//{
//	objects.clear();
//	root = nullptr;
//}
//
//void QuadTree::Init(D3DXVECTOR2 camSize, D3DXVECTOR2 mapSize, std::vector<LPOBJECT> listObj)
//{
//	this->cameraSize = camSize;
//	this->mapSize = mapSize;
//	this->objects = listObj;
//
//	Build(this->root);
//}
//
//std::vector<LPOBJECT> QuadTree::GetObjectsInCamera(LPCAMERA camera)
//{
//	std::vector<LPOBJECT> ObjectsInView;
//	objects.clear();
//	GetObjects(root, camera, ObjectsInView);
//
//	//Khu trung lap
//	std::set<int> s(ObjectsInView.begin(), ObjectsInView.end());
//	ObjectsInView.assign(s.begin(), s.end());
//
//	return  ObjectsInView;
//}
//
//void QuadTree::Build(QTNode*& node)
//{
//	if (node == nullptr) {
//		node = new QTNode(0, 0, mapSize.x - 1, mapSize.y - 1);
//		node->objects = this->objects;
//	}
//
//	if (CheckNodeSize(node) && node->objects.size() > 0) {
//		long x_mid = (node->right - node->left) / 2;
//		long y_mid = (node->right - node->left) / 2;
//		node->childrens[0] = new QTNode(node->left, node->top, x_mid, y_mid);
//		node->childrens[1] = new QTNode(x_mid + 1, node->top, node->right, y_mid);
//		node->childrens[2] = new QTNode(node->left, y_mid + 1, x_mid, node->bottom);
//		node->childrens[3] = new QTNode(x_mid + 1, y_mid + 1, node->right, node->bottom);
//
//		for each (LPOBJECT obj in node->objects)
//		{
//			long left = obj->CollisionBox().left;
//			long right = obj->CollisionBox().right;
//			long top = obj->CollisionBox().top;
//			long bottom = obj->CollisionBox().bottom;
//
//			for (int i = 0; i < 4; i++)
//			{   //Kiem tra object co nam trong node con khong?
//				if (left <= node->childrens[i]->right
//					&&	right >= node->childrens[i]->left
//					&&	top <= node->childrens[i]->bottom
//					&&	bottom >= node->childrens[i]->top
//					)
//				{
//					node->childrens[i]->objects.push_back(obj);
//				}
//			}
//		}
//
//		Build(node->childrens[0]);
//		Build(node->childrens[1]);
//		Build(node->childrens[2]);
//		Build(node->childrens[3]);
//	}
//}
//
//void QuadTree::GetObjects(QTNode* node, LPCAMERA camera, std::vector<LPOBJECT>& ObjectsInView)
//{
//	if (node != nullptr) {
//		//Kiem tra node co nam trong viewport khong?
//		if (camera->Border().left <= node->right
//			&& camera->Border().top <= node->bottom
//			&& camera->Border().right >= node->left
//			&& camera->Border().bottom >= node->top
//			)
//		{
//			//Kiem tra day co phai node la khong?
//			if (node->childrens == nullptr) {
//				//Them cac object vao cho danh sach can lay
//				for each (LPOBJECT obj in node->objects)
//				{
//					ObjectsInView.push_back(obj);
//				}
//			}
//			else
//			{
//				//Neu khong phai node la thi tiep tuc de quy voi cac node con cua no
//				GetObjects(node->childrens[0], camera, objects);
//				GetObjects(node->childrens[1], camera, objects);
//				GetObjects(node->childrens[2], camera, objects);
//				GetObjects(node->childrens[3], camera, objects);
//			}
//		}
//	}
//}
//
//
//bool QuadTree::CheckNodeSize(QTNode* node)
//{
//	long w = node->right - node->left + 1;
//	long h = node->bottom - node->top + 1;
//	if (w > this->cameraSize.x && h > this->cameraSize.y) {
//		return true;
//	}
//	return false;
//}
//
//QuadTree::~QuadTree()
//{
//}
//
//
//QTNode::QTNode(long l, long t, long r, long b)
//{
//	childrens[0] = { nullptr };
//	left = l;
//	top = t;
//	right = r;
//	bottom = b;
//	objects.clear();
//}
//
//QTNode::~QTNode()
//{
//}
