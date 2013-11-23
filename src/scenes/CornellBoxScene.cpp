
#include <iostream>
#include "CornellBoxScene.h"
#include "renderer/Sphere.h"
#include "renderer/Polygon.h"
#include "renderer/SphereLight.h"

namespace OmochiRenderer {

CornellBoxScene::CornellBoxScene()
{
  AddObject(new Sphere(1e5, Vector3( 1e5+1, 40.8, 81.6),  Material(Material::REFLECTION_TYPE_LAMBERT, Color(), Color(0.75, 0.25, 0.25))), true, false);  // ��
  AddObject(new Sphere(1e5, Vector3(-1e5+99, 40.8, 81.6), Material(Material::REFLECTION_TYPE_LAMBERT, Color(), Color(0.25, 0.25, 0.75))), true, false);  // �E
  AddObject(new Sphere(1e5, Vector3(50, 40.8,  1e5),      Material(Material::REFLECTION_TYPE_LAMBERT, Color(), Color(0.75, 0.75, 0.75))), true, false);  // ��
  AddObject(new Sphere(1e5, Vector3(50, 40.8, -1e5+250),    Material(Material::REFLECTION_TYPE_LAMBERT, Color(), Color())), true, false);                  // ��O
  AddObject(new Sphere(1e5, Vector3(50,  1e5,      81.6), Material(Material::REFLECTION_TYPE_LAMBERT, Color(), Color(0.75, 0.75, 0.75))), true, false);  // ��
  AddObject(new Sphere(1e5, Vector3(50, -1e5+81.6, 81.6), Material(Material::REFLECTION_TYPE_LAMBERT, Color(), Color(0.75, 0.75, 0.75))), true, false);  // ��
  AddObject(new Sphere(20,Vector3(50, 20, 50),           Material(Material::REFLECTION_TYPE_LAMBERT,    Color(), Color(0.25, 0.75, 0.25))));    // �΋�
  AddObject(new Sphere(16.5,Vector3(19, 16.5, 25),       Material(Material::REFLECTION_TYPE_SPECULAR,   Color(), Color(0.99, 0.99, 0.99))));   // ��
  AddObject(new Sphere(16.5, Vector3(77, 16.5, 78), Material(Material::REFLECTION_TYPE_REFRACTION, Color(), Color(0.99, 0.99, 0.99), REFRACTIVE_INDEX_OBJECT))); // �K���X
  SphereLight *sphereLight = new SphereLight(7.5, Vector3(50.0, 72.5, 81.6), Material(Material::REFLECTION_TYPE_LAMBERT, Color(16, 16, 16), Color()));
  AddObject(sphereLight);    // �Ɩ�

  //AddObject(new Sphere(16.5, Vector3(27, 16.5, 47), Material(Material::REFLECTION_TYPE_SPECULAR, Color(), Color(0.99, 0.99, 0.99))));   // ��
  //AddObject(new Sphere(16.5, Vector3(73, 16.5, 78), Material(Material::REFLECTION_TYPE_REFRACTION, Color(), Color(0.99, 0.99, 0.99), REFRACTIVE_INDEX_OBJECT))); // �K���X
  //SphereLight *sphereLight = new SphereLight(5, Vector3(50.0, 75, 81.6), Material(Material::REFLECTION_TYPE_LAMBERT, Color(12, 12, 12), Color()));
  //AddObject(sphereLight);    // �Ɩ�

  //ConstructQBVH();
}

}
