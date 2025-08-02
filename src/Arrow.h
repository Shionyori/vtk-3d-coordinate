// src/Arrow.h
#pragma once

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkLineSource.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkMath.h>

class Arrow
{
public:
    Arrow();
    Arrow(
        double origin[3], 
        double target[3], 
        int coneCount = 1, 
        double color[3] = nullptr, 
        double lineWidth = 1.5
    );
    
    void CreateArrow(
        double origin[3], 
        double target[3], 
        int coneCount = 1, 
        double color[3] = nullptr, 
        double lineWidth = 1.5
    );

    vtkActor* GetLineActor() { return m_line; }
    vtkActor* GetCone1Actor() { return m_cone1; }
    vtkActor* GetCone2Actor() { return m_cone2; }
    int GetConeCount() const { return m_coneCount; }
    
private:
    int m_coneCount = 0;

    vtkSmartPointer<vtkActor>       m_line;
    vtkSmartPointer<vtkActor>       m_cone1;
    vtkSmartPointer<vtkActor>       m_cone2;

    vtkSmartPointer<vtkLineSource>  m_lineSource;
    vtkSmartPointer<vtkConeSource>  m_coneSource1;
    vtkSmartPointer<vtkConeSource>  m_coneSource2;
};