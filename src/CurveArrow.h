// include/CurveArrow.h
#pragma once

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkActor.h>
#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkConeSource.h>

class CurveArrow
{
public:
    CurveArrow();
    CurveArrow(vtkSmartPointer<vtkPoints> points, int coneCount = 1, double color[3] = nullptr, float lineWidth = 3.0);
    void CreateCurveArrow(vtkSmartPointer<vtkPoints> points, int coneCount = 1, double color[3] = nullptr, float lineWidth = 3.0);
    vtkSmartPointer<vtkActor> GetCurveActor() const { return m_curve; }
    vtkSmartPointer<vtkActor> GetCone1Actor() const { return m_cone1; }
    vtkSmartPointer<vtkActor> GetCone2Actor() const { return m_cone2; }

private:
    int m_coneCount = 0; 
    vtkSmartPointer<vtkActor> m_curve = nullptr;
    vtkSmartPointer<vtkActor> m_cone1 = nullptr; 
    vtkSmartPointer<vtkActor> m_cone2 = nullptr; 

    vtkSmartPointer<vtkParametricSpline> m_spline = nullptr; // 参数化样条曲线
    vtkSmartPointer<vtkParametricFunctionSource> m_functionSource = nullptr; // 参数化函数源
    vtkSmartPointer<vtkConeSource> m_coneSource1 = nullptr; 
    vtkSmartPointer<vtkConeSource> m_coneSource2 = nullptr; 
};