#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/compute_normal.h>
#include <iostream>
#include <fstream>
#include <pcl/point_types.h>
#include <pcl/features/fpfh.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point;
typedef K::Vector_3 Vector;
typedef CGAL::Surface_mesh<Point> Surface_mesh;
typedef boost::graph_traits<Surface_mesh>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<Surface_mesh>::face_descriptor   face_descriptor;
int main(int argc, char* argv[])
{
  const char* filename = (argc > 1) ? argv[1] : "../../data/chair_0001.off";
  std::cout << filename<< std::endl;
  std::ifstream input(filename);
  Surface_mesh mesh;
  if (!input || !(input >> mesh) || mesh.is_empty()) {
    std::cerr << "Not a valid off file." << std::endl;
    return 1;
  }
  auto fnormals = mesh.add_property_map<face_descriptor, Vector>
      ("f:normals", CGAL::NULL_VECTOR).first;
  auto vnormals = mesh.add_property_map<vertex_descriptor, Vector>
      ("v:normals", CGAL::NULL_VECTOR).first;
  CGAL::Polygon_mesh_processing::compute_normals(mesh,
        vnormals,
        fnormals,
        CGAL::Polygon_mesh_processing::parameters::vertex_point_map(mesh.points()).
        geom_traits(K()));
//  std::cout << "Face normals :" << std::endl;
//  for(face_descriptor fd: faces(mesh)){
//    std::cout << fnormals[fd] << std::endl;
//  }
//  std::cout << "Vertex normals :" << std::endl;
//  for(vertex_descriptor vd: vertices(mesh)){
//    std::cout << vnormals[vd] << std::endl;
//  }
//  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
//  pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());
//    int i = 0;
//      for(vertex_descriptor vd: vertices(mesh)){
//         normals->points[i].normal_x = vnormals[vd].hx();
//         normals->points[i].normal_y = vnormals[vd].hy();
//         normals->points[i].normal_z = vnormals[vd].hz();
//      }
//      i = 0;
//  for(vertex_descriptor vd : mesh.vertices()){
////      cloud(pcl::PointXYZ(mesh.points()[vd].hx(), mesh.points()[vd].hy(), mesh.points()[vd].hz()));
//      cloud->points[i].x = mesh.points()[vd].hx();
//      cloud->points[i].y = mesh.points()[vd].hy();
//      cloud->points[i].z = mesh.points()[vd].hz();
//      i++;
//  }

//  pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh;
//  fpfh.setInputCloud (cloud);
//  fpfh.setInputNormals (normals);
//  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);

//  fpfh.setSearchMethod (tree);
//    pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs (new pcl::PointCloud<pcl::FPFHSignature33> ());
//    fpfh.setRadiusSearch (0.05);
//  fpfh.compute (*fpfhs);
  return 0;
}
