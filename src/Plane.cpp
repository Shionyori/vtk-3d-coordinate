#include "Plane.h"

Plane::Plane() = default;

Plane::Plane(double origin[3], double point1[3], double point2[3], double width, double color[3])
{
    createPlane(origin, point1, point2, width, color);
}

void Plane::createPlane(double origin[3], double point1[3], double point2[3], double width, double color[3])
{
    m_planeSource = vtkSmartPointer<vtkPlaneSource>::New();
    vtkNew<vtkPolyDataMapper> PlaneMapper;
    m_plane = vtkSmartPointer<vtkActor>::New();

    m_planeSource->SetOrigin(origin);
    m_planeSource->SetPoint1(point1);
    m_planeSource->SetPoint2(point2);

    m_planeSource->Update();

    m_planeLinearExtrusionFilter = vtkSmartPointer<vtkLinearExtrusionFilter>::New();
    m_planeLinearExtrusionFilter->SetInputConnection(m_planeSource->GetOutputPort());
    m_planeLinearExtrusionFilter->SetExtrusionTypeToNormalExtrusion();

    double vec[3] {1, 0, 0};
    m_planeLinearExtrusionFilter->SetVector(vec);
    m_planeLinearExtrusionFilter->SetScaleFactor(width);

    m_planeTriangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
    m_planeTriangleFilter->SetInputConnection(m_planeLinearExtrusionFilter->GetOutputPort());

    PlaneMapper->SetInputConnection(m_planeLinearExtrusionFilter->GetOutputPort());
    m_plane->SetMapper(PlaneMapper);
    m_plane->GetProperty()->SetColor(color);
}