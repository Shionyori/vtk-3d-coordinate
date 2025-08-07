// src/Arrow.cpp
#include "Arrow.h"
#include <vtkProperty.h>

Arrow::Arrow() = default;

Arrow::Arrow(
        double origin[3], 
        double target[3], 
        int coneCount, 
        double color[3], 
        double lineWidth)
{
    CreateArrow(origin, target, coneCount, color, lineWidth);
}

void Arrow::CreateArrow(
        double origin[3], 
        double target[3], 
        int coneCount, 
        double color[3], 
        double lineWidth)
{
    // 清空旧数据
    m_lineSource  = nullptr;
    m_coneSource1 = nullptr;
    m_coneSource2 = nullptr;
    m_line        = nullptr;
    m_cone1       = nullptr;
    m_cone2       = nullptr;
    m_coneCount   = coneCount;

    // 直线
    m_lineSource = vtkSmartPointer<vtkLineSource>::New();
    m_lineSource->SetPoint1(origin);
    m_lineSource->SetPoint2(target);

    auto lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    lineMapper->SetInputConnection(m_lineSource->GetOutputPort());

    m_line = vtkSmartPointer<vtkActor>::New();
    m_line->SetMapper(lineMapper);
    m_line->GetProperty()->SetLineWidth(lineWidth);
    if(color) m_line->GetProperty()->SetColor(color);

    // 方向向量
    double dir[3] = {0};
    vtkMath::Subtract(target, origin, dir);

    // 箭头
    if(coneCount >= 1)
    {
        m_coneSource1 = vtkSmartPointer<vtkConeSource>::New();
        m_coneSource1->SetCenter(target);
        m_coneSource1->SetHeight(0.25);
        m_coneSource1->SetRadius(0.04);
        m_coneSource1->SetResolution(10);
        m_coneSource1->SetDirection(dir);

        auto coneMapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
        coneMapper1->SetInputConnection(m_coneSource1->GetOutputPort());

        m_cone1 = vtkSmartPointer<vtkActor>::New();
        m_cone1->SetMapper(coneMapper1);
        if (color) m_cone1->GetProperty()->SetColor(color);
    }
    if (coneCount >= 2)
    {
        double revDir[3] = { -dir[0], -dir[1], -dir[2] };

        m_coneSource2 = vtkSmartPointer<vtkConeSource>::New();
        m_coneSource2->SetCenter(origin);
        m_coneSource2->SetHeight(0.25);
        m_coneSource2->SetRadius(0.04);
        m_coneSource2->SetResolution(10);
        m_coneSource2->SetDirection(revDir);

        auto coneMapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
        coneMapper2->SetInputConnection(m_coneSource2->GetOutputPort());

        m_cone2 = vtkSmartPointer<vtkActor>::New();
        m_cone2->SetMapper(coneMapper2);
        if (color) m_cone2->GetProperty()->SetColor(color);
    }

    m_coneCount = coneCount;
}
