#include <vtkSmartPointer.h>

#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

int main()
{
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();

    sphereSource->SetRadius(0.2); // 设置球体的半径
    sphereSource->SetCenter(0.0, 0.0, 0.0); // 设置球体的中心
    sphereSource->SetPhiResolution(15); // 设置球体的经向分辨率
    sphereSource->SetThetaResolution(15); // 设置球体的纬向分辨率

    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
    sphereActor->SetMapper(sphereMapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    renderer->SetBackground(0.1, 0.2, 0.3); // 设置背景颜色

    renderer->AddActor(sphereActor);
    renWin->AddRenderer(renderer);
    iren->SetRenderWindow(renWin);

    renWin->Render();
    iren->Initialize();
    iren->Start();

    return 0;
}