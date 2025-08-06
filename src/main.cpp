#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

#include "Arrow.h"
#include "CurveArrow.h"

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

    /* 3. 创建逆时针的曲线箭头 */
    vtkNew<vtkPoints> xToYPoints;
    xToYPoints->InsertNextPoint(xEnd);
    xToYPoints->InsertNextPoint(1.0, 1.0, 0.0);
    xToYPoints->InsertNextPoint(yEnd);

    vtkNew<vtkPoints> yToZPoints;
    yToZPoints->InsertNextPoint(yEnd);
    yToZPoints->InsertNextPoint(0.0, 1.0, 1.0);
    yToZPoints->InsertNextPoint(zEnd);

    vtkNew<vtkPoints> zToXPoints;
    zToXPoints->InsertNextPoint(zEnd);
    zToXPoints->InsertNextPoint(1.0, 0.0, 1.0);
    zToXPoints->InsertNextPoint(xEnd);

    // X 到 Y 的曲线箭头 (黄色)
    double yellow[3] = {1.0, 1.0, 0.0};
    CurveArrow xToYArrow(xToYPoints, 1, yellow, 2.0);

    // Y 到 Z 的曲线箭头 (青色)
    double cyan[3] = {0.0, 1.0, 1.0};
    CurveArrow yToZArrow(yToZPoints, 1, cyan, 2.0);

    // Z 到 X 的曲线箭头 (品红色)
    double magenta[3] = {1.0, 0.0, 1.0};
    CurveArrow zToXArrow(zToXPoints, 1, magenta, 2.0);

    /* 4. 把 Actor 加入场景 */
    renderer->AddActor(xArrow.GetLineActor());
    renderer->AddActor(xArrow.GetCone1Actor());

    renderer->AddActor(yArrow.GetLineActor());
    renderer->AddActor(yArrow.GetCone1Actor());

    renderer->AddActor(zArrow.GetLineActor());
    renderer->AddActor(zArrow.GetCone1Actor());

    renderer->AddActor(xToYArrow.GetCurve());
    renderer->AddActor(xToYArrow.GetCone1());

    renderer->AddActor(yToZArrow.GetCurve());
    renderer->AddActor(yToZArrow.GetCone1());

    renderer->AddActor(zToXArrow.GetCurve());
    renderer->AddActor(zToXArrow.GetCone1());

    /* 5. 渲染与交互 */
    renderer->SetBackground(0.1, 0.1, 0.1);  // 黑灰背景
    renWin->SetSize(800, 600);
    renWin->SetWindowName("VTK Coordinate Axes with Curved Arrows");
    renWin->Render();
    renWinI->Start();

    return 0;
}