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
    // 默认构造函数
    CurveArrow();

    // 带参数的构造函数
    CurveArrow(vtkSmartPointer<vtkPoints> points, int coneCount = 1, double color[3] = nullptr, float lineWidth = 3.0);

    // 创建曲线箭头
    void CreateArrow(vtkSmartPointer<vtkPoints> points, int coneCount = 1, double color[3] = nullptr, float lineWidth = 3.0);

    // 获取曲线和箭头的 Actor
    vtkSmartPointer<vtkActor> GetCurve() const { return m_curve; }
    vtkSmartPointer<vtkActor> GetCone1() const { return m_cone1; }
    vtkSmartPointer<vtkActor> GetCone2() const { return m_cone2; }

private:
    int m_coneCount = 0; // 箭头数量
    vtkSmartPointer<vtkActor> m_curve = nullptr; // 曲线部分
    vtkSmartPointer<vtkActor> m_cone1 = nullptr; // 箭头1
    vtkSmartPointer<vtkActor> m_cone2 = nullptr; // 箭头2

    vtkSmartPointer<vtkParametricSpline> m_spline = nullptr; // 参数化样条曲线
    vtkSmartPointer<vtkParametricFunctionSource> m_functionSource = nullptr; // 参数化函数源
    vtkSmartPointer<vtkConeSource> m_coneSource1 = nullptr; // 箭头1的锥体源
    vtkSmartPointer<vtkConeSource> m_coneSource2 = nullptr; // 箭头2的锥体源
};