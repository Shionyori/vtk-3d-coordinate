// src/CurveArrow.cpp
#include "CurveArrow.h"
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricSpline.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkConeSource.h>
#include <vtkMath.h>

CurveArrow::CurveArrow() = default;

CurveArrow::CurveArrow(vtkSmartPointer<vtkPoints> points, int coneCount, double color[3], float lineWidth)
{
    CreateArrow(points, coneCount, color, lineWidth);
}

void CurveArrow::CreateArrow(vtkSmartPointer<vtkPoints> points, int coneCount, double color[3], float lineWidth)
{
    // 清空旧数据
    m_curve = nullptr;
    m_cone1 = nullptr;
    m_cone2 = nullptr;
    m_spline = nullptr;
    m_functionSource = nullptr;
    m_coneSource1 = nullptr;
    m_coneSource2 = nullptr;

    if (points->GetNumberOfPoints() < 2)
    {
        throw std::invalid_argument("Input points must have at least two points!");
    }

    // 曲线部分
    m_spline = vtkSmartPointer<vtkParametricSpline>::New();
    m_functionSource = vtkSmartPointer<vtkParametricFunctionSource>::New();
    m_spline->SetPoints(points);
    m_functionSource->SetParametricFunction(m_spline);
    m_functionSource->Update();

    auto lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    lineMapper->SetInputConnection(m_functionSource->GetOutputPort());

    m_curve = vtkSmartPointer<vtkActor>::New();
    m_curve->SetMapper(lineMapper);
    m_curve->GetProperty()->SetLineWidth(lineWidth);
    if (color) m_curve->GetProperty()->SetColor(color);

    // 箭头部分
    double directVec[3] = {0};
    int pointsNum = points->GetNumberOfPoints();
    double target[3] = {0}, origin[3] = {0};

    // 获取最后一个点和倒数第二个点
    points->GetPoint(pointsNum - 1, target);
    points->GetPoint(pointsNum - 2, origin);
    vtkMath::Subtract(target, origin, directVec);

    // 箭头1
    m_coneCount = coneCount;
    if (coneCount >= 1)
    {
        m_coneSource1 = vtkSmartPointer<vtkConeSource>::New();
        m_coneSource1->SetCenter(target);
        m_coneSource1->SetHeight(0.5);
        m_coneSource1->SetRadius(0.08);
        m_coneSource1->SetResolution(10);
        m_coneSource1->SetDirection(directVec);

        auto coneMapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
        coneMapper1->SetInputConnection(m_coneSource1->GetOutputPort());

        m_cone1 = vtkSmartPointer<vtkActor>::New();
        m_cone1->SetMapper(coneMapper1);
        if (color) m_cone1->GetProperty()->SetColor(color);
    }

    // 箭头2
    if (coneCount >= 2)
    {
        points->GetPoint(0, target);
        points->GetPoint(1, origin);
        vtkMath::Subtract(target, origin, directVec);

        m_coneSource2 = vtkSmartPointer<vtkConeSource>::New();
        m_coneSource2->SetCenter(origin);
        m_coneSource2->SetHeight(0.5);
        m_coneSource2->SetRadius(0.08);
        m_coneSource2->SetResolution(10);
        m_coneSource2->SetDirection(directVec);

        auto coneMapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
        coneMapper2->SetInputConnection(m_coneSource2->GetOutputPort());

        m_cone2 = vtkSmartPointer<vtkActor>::New();
        m_cone2->SetMapper(coneMapper2);
        if (color) m_cone2->GetProperty()->SetColor(color);
    }
}