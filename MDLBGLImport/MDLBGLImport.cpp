// MDLBGLImport.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "MDLBGLImport.h"

BOOL objFileRead(const TCHAR *filename, Mesh *mesh)
{
	float size, h;

	h = 0.5 * 5;

	// Число вершин и граней в меш
	mesh->setNumVerts(8);
	mesh->setNumFaces(12);
	// Координаты вершин
	mesh->setVert(0, Point3(-h, -h, -h));
	mesh->setVert(1, Point3(h, -h, -h));
	mesh->setVert(2, Point3(-h, h, -h));
	mesh->setVert(3, Point3(h, h, -h));
	mesh->setVert(4, Point3(-h, -h, h));
	mesh->setVert(5, Point3(h, -h, h));
	mesh->setVert(6, Point3(-h, h, h));
	mesh->setVert(7, Point3(h, h, h));
	// Состав граней
	mesh->faces[0].setVerts(0, 2, 3);
	mesh->faces[1].setVerts(3, 1, 0);
	mesh->faces[2].setVerts(4, 5, 7);
	mesh->faces[3].setVerts(7, 6, 4);
	mesh->faces[4].setVerts(0, 1, 5);
	mesh->faces[5].setVerts(5, 4, 0);
	mesh->faces[6].setVerts(1, 3, 7);
	mesh->faces[7].setVerts(7, 5, 1);
	mesh->faces[8].setVerts(3, 2, 6);
	mesh->faces[9].setVerts(6, 7, 3);
	mesh->faces[10].setVerts(2, 0, 4);
	mesh->faces[11].setVerts(4, 6, 2);
	// Группы сглаживания
	mesh->faces[0].setSmGroup(2);
	mesh->faces[1].setSmGroup(2);
	mesh->faces[2].setSmGroup(4);
	mesh->faces[3].setSmGroup(4);
	mesh->faces[4].setSmGroup(8);
	mesh->faces[5].setSmGroup(8);
	mesh->faces[6].setSmGroup(16);
	mesh->faces[7].setSmGroup(16);
	mesh->faces[8].setSmGroup(32);
	mesh->faces[9].setSmGroup(32);
	mesh->faces[10].setSmGroup(64);
	mesh->faces[11].setSmGroup(64);
	// Устанавливаем видимость внешних ребер граней (диагональные ребра не видны)
	for (int k = 0; k < 12; k++) {
		mesh->faces[k].setEdgeVisFlags(1, 1, 0);
		mesh->faces[k].setMatID(1);
	}
	// Назначаем UVW-координаты
	Matrix3 tm(1);
	tm.Scale(Point3(h, h, h));
	tm = Inverse(tm);
	mesh->ApplyUVWMap(MAP_BOX, 1.0f, 1.0f, 1.0f, 0, 0, 0, 0, tm);
	mesh->InvalidateTopologyCache();
	return TRUE;
#pragma message(TODO("return TRUE If the file is imported properly"))
}


	int MDLBGLImport::DoImport(const TCHAR * filename, ImpInterface * i, Interface * gi, BOOL suppressPrompts)
	{
		TriObject *object = CreateNewTriObject();
		if (!object)
			return 0;

		if (objFileRead(filename, &object->GetMesh())) {
			INode *node = gi->CreateObjectNode(object);
			if (!node) {
				delete object;
				return FALSE;
			}
			Matrix3 tm;
			tm.IdentityMatrix();
			//node->Reference(object);
			node->SetNodeTM(0, tm);
			//gi->AddNodeToScene(node);
			node->SetName(L"TestMesh");
			Class_ID P3DMat = { 0x7e8caded , 0xb6928000 };
			Mtl *mtlb = (Mtl*)gi->CreateInstance(MATERIAL_CLASS_ID, P3DMat);
			gi->PutMtlToMtlEditor(mtlb);
			INode* node1 = node;
			mtlb->SetName(TSTR(_T("OUT")));
			node->SetMtl(mtlb);
			mtlb->SetDiffuse(Color(0.4, 0.7, 1.0), 0);
			bool bFresnelDiffuse = true;
			mtlb->SetProperty(PROPID_USER + 1, &bFresnelDiffuse);
			bFresnelDiffuse = mtlb->GetProperty(PROPID_USER + 1);
			int PBN = mtlb->NumParamBlocks();
			IParamBlock2 *PB = mtlb->GetParamBlock(0);
			ParamBlockDesc2* desc = PB->GetDesc();
			int NP = desc->Count();
			ParamDef mc;
			PB->SetValue(0, 0, true, 0);
			//PB->SetDesc(desc);
			int PID = desc->NameToIndex(L"bFresnelDiffuse");
			for (int ii = 0; ii < NP; ii++)
			{

				mc = desc->paramdefs[ii];
			}
			//ParamAlias *PA = PB->FindParamAlias(TSTR(_T("bFresnelDiffuse")));
			//ParamAlias *PA2 = PB->FindParamAlias(TSTR(_T("ui:bDiffuse")));
			//mtlb->SetProperty(PA->ID, &bFresnelDiffuse);
			//mtlb->SetProperty();1
			/*gi->LoadDefaultMatLib();
			MtlBaseLib &ml = *gi->GetSceneMtls();



			//int mli = ml->FindMtlByName(TSTR(_T("Prepar3D")));
			int count = ml.Count();
			//int index = mlib1.FindMtlByName(TSTR(_T("Prepar3D")));
			if (count <= 0)
			{
			return FALSE;
			}
			//Mtl *m1 = new Mtl();
			MtlBase *m2 = ml[0];
			Class_ID class1 = m2->ClassID();

			//m->ActivateTexDisplay(FALSE);

			if (gi->GetSelNodeCount() < 1)
			{
			return TRUE;
			}
			//INode *node = gi->GetSelNode(0);*/
			i->RedrawViews();
			return TRUE;
		}
		return FALSE;
	}
