#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

#include "Arrow.h"

int main()
{
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renWin;
    vtkNew<vtkRenderWindowInteractor> renWinI;

    renWin->AddRenderer(renderer);
    renWinI->SetRenderWindow(renWin);
    renWinI->Initialize();

    /* 2. 创建 X、Y、Z 三条坐标轴箭头 */
    double origin[3] = {0.0, 0.0, 0.0};

    // X 轴 (红色)
    double xEnd[3] = {2.0, 0.0, 0.0};
    double red[3]  = {1.0, 0.0, 0.0};
    Arrow xArrow(origin, xEnd, 1, red, 2.5);

    // Y 轴 (绿色)
    double yEnd[3] = {0.0, 2.0, 0.0};
    double green[3] = {0.0, 1.0, 0.0};
    Arrow yArrow(origin, yEnd, 1, green, 2.5);

    // Z 轴 (蓝色)
    double zEnd[3] = {0.0, 0.0, 2.0};
    double blue[3] = {0.0, 0.0, 1.0};
    Arrow zArrow(origin, zEnd, 1, blue, 2.5);

    /* 3. 把 Actor 加入场景 */
    renderer->AddActor(xArrow.GetLineActor());
    renderer->AddActor(xArrow.GetCone1Actor());

    renderer->AddActor(yArrow.GetLineActor());
    renderer->AddActor(yArrow.GetCone1Actor());

    renderer->AddActor(zArrow.GetLineActor());
    renderer->AddActor(zArrow.GetCone1Actor());

    /* 4. 渲染与交互 */
    renderer->SetBackground(0.1, 0.1, 0.1);  // 黑灰背景
    renWin->SetSize(800, 600);
    renWin->SetWindowName("VTK Coordinate Axes");
    renWin->Render();
    renWinI->Start();

    return 0;
}