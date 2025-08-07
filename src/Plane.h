#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPlaneSource.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

class Plane
{
public: 
    Plane();
    Plane(double origin[3], double point1[3], double point2[3], double width, double color[3]);
    void createPlane(double origin[3], double point1[3], double point2[3], double width, double color[3]);
    
    vtkSmartPointer<vtkActor> GetPlaneActor() { return m_plane; }

private:
    vtkSmartPointer<vtkActor> m_plane;
    vtkSmartPointer<vtkPlaneSource> m_planeSource;
    vtkSmartPointer<vtkLinearExtrusionFilter> m_planeLinearExtrusionFilter;
    vtkSmartPointer<vtkTriangleFilter> m_planeTriangleFilter;
};