#include "Graphics.h"

const char* vertexShaderCode = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderCode = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.0f, 0.3f, 1.0f);\n"
"}\n\0";

Graphics::Graphics()
{
    window = nullptr;
    submited = false;
}

int Graphics::init()
{
    if (glfwInit() == 0)
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1000, 800, "Castle Wars", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create the window !\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glViewport(0, 0, 1000, 800);

    const char *glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return 1;
}

void Graphics::draw(Resources player, Resources enemy, Card deck[8], char *playerName, char *enemyName, bool yourTurn, bool gameOver, char *winner)
{
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    // ImGui::ShowDemoWindow(&show_demo_window);

    if (gameOver == true)
    {
        ImGui::SetNextWindowPos(ImVec2(435, 350));
        ImGui::SetNextWindowSize(ImVec2(200, 100));
        if (ImGui::Begin("Win", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
        {
            ImGui::SetNextWindowPos(ImVec2(435, 350));
            ImGui::SetNextWindowSize(ImVec2(200, 100));
            ImGui::SetCursorPosY(5);
            ImGui::Text("%s won the game.", winner);
        }
        ImGui::End();
    }


    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(1000, 40));
    if (ImGui::Begin("Header", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(1000, 45));
        ImGui::SetCursorPosX(120 - ImGui::CalcTextSize(playerName).x);
        ImGui::SetCursorPosY(5);
        ImGui::Text("%s", playerName);

        ImGui::SetCursorPosX(440);
        ImGui::SetCursorPosY(5);
        if (yourTurn == true)
        {
            ImGui::Text("Its %s's turn", playerName);
        }
        else
        {
            ImGui::Text("Its %s's turn", enemyName);
        }

        ImGui::SetCursorPosX(880);
        ImGui::SetCursorPosY(5);
        ImGui::Text("%s", enemyName);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, 50));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("First", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(0, 50));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Builders : %d", player.builders);
        ImGui::Text("Bricks : %d", player.bricks);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, 120));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("Second", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(0, 120));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Soldiers : %d", player.soldiers);
        ImGui::Text("Weapons : %d", player.weapons);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, 190));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("Third", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(0, 190));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Magic : %d", player.magic);
        ImGui::Text("Crystals : %d", player.crystals);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, 260));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("Fourth", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(0, 260));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Castle : %d", player.castle);
        ImGui::Text("Fence : %d", player.fence);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(880, 50));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("Fifth", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(850, 50));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Builders : %d", enemy.builders);
        ImGui::Text("Bricks : %d", enemy.bricks);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(880, 120));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("Sixth", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(880, 120));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Soldiers : %d", enemy.soldiers);
        ImGui::Text("Weapons : %d", enemy.weapons);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(880, 190));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("Seventh", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(880, 190));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Magic : %d", enemy.magic);
        ImGui::Text("Crystals : %d", enemy.crystals);
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(880, 260));
    ImGui::SetNextWindowSize(ImVec2(120, 50));
    if (ImGui::Begin("Eighth", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(880, 260));
        ImGui::SetNextWindowSize(ImVec2(120, 50));
        ImGui::Text("Castle : %d", enemy.castle);
        ImGui::Text("Fence : %d", enemy.fence);
    }
    ImGui::End();

    for (int i = 0; i < 8; i++)
    {
        deck[i].draw(player);
    }

    ImGui::Render();

    glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::drawWelcome(bool &playPressed)
{
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    /*ImGuiStyle& style = ImGui::GetStyle();
    ImGuiStyle initStyle = style;
    style*/

    ImGui::SetNextWindowPos(ImVec2(450, 365));
    ImGui::SetNextWindowSize(ImVec2(100, 60));
    if (ImGui::Begin("PLAY-SCREEN", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
    {
        ImGui::SetNextWindowPos(ImVec2(450, 365));
        ImGui::SetNextWindowSize(ImVec2(100, 60));
        ImGui::SetCursorPos(ImVec2(5, 5));
        ImGui::SetWindowFontScale(2);
        if (ImGui::Button("PLAY", ImVec2(90, 50)))
        {
            playPressed = true;
        }
    }
    ImGui::End();

    ImGui::Render();

    glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::drawRooms(bool &createRoomPressed, bool &joinRoomPressed, std::string &joinedRoom, std::vector<Room> rooms)
{
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(50, 50));
    ImGui::SetNextWindowSize(ImVec2(900, 600));
    if (ImGui::Begin("ROOMS", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
        int yPos = 70;
        ImGui::SetNextWindowPos(ImVec2(50, yPos));
        ImGui::SetNextWindowSize(ImVec2(900, 100));
        for (int i = 0; i < rooms.size(); i++)
        {
            if (ImGui::Begin(rooms[i].name.c_str(), NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                ImGui::SetCursorPos(ImVec2(400, yPos - (i * 100)));
                if (ImGui::Button("Join Room", ImVec2(40, 20)))
                {
                    // rooms[i].joined = true;
                    joinedRoom = rooms[i].name;
                    joinRoomPressed = true;
                }
            }
            ImGui::End();
            yPos += 100;
            ImGui::SetNextWindowPos(ImVec2(50, yPos));
            ImGui::SetNextWindowSize(ImVec2(900, 100));
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(400, 660));
    ImGui::SetNextWindowSize(ImVec2(210, 60));
    if (ImGui::Begin("CREATE ROOM", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
    {
        ImGui::SetNextWindowPos(ImVec2(400, 660));
        ImGui::SetNextWindowSize(ImVec2(210, 60));
        ImGui::SetCursorPos(ImVec2(5, 5));
        ImGui::SetWindowFontScale(2);
        if (ImGui::Button("Create Room", ImVec2(200, 50)))
        {
            createRoomPressed = true;
        }
    }
    ImGui::End();

    ImGui::Render();

    glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::drawWaitingEnemy(char *name, bool &submit)
{
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(435, 350));
    ImGui::SetNextWindowSize(ImVec2(200, 100));
    if (ImGui::Begin("TYPE NAME", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(435, 350));
        ImGui::SetNextWindowSize(ImVec2(200, 100));
        if (submited == false)
        {
            ImGui::SetCursorPosX(35);
            ImGui::Text("Your name :");
            ImGui::SetCursorPosX(35);
            ImGui::InputText("##", name, CHAR_MAX);
            ImGui::SetCursorPosX(35);
            if (ImGui::Button("Submit", ImVec2(130, 40)))
            {
                submit = true;
                submited = true;
            }
        }
        else
        {
            ImGui::SetCursorPosY(40);
            ImGui::Text("Waiting for a second player");
            switch (dotNumber)
            {
            case 1:
                ImGui::SetCursorPosY(50);
                ImGui::SetCursorPosX(90);
                ImGui::Text(".");
                break;
            case 2:
                ImGui::SetCursorPosY(50);
                ImGui::SetCursorPosX(90);
                ImGui::Text("..");
                break;
            case 3:
                ImGui::SetCursorPosY(50);
                ImGui::SetCursorPosX(90);
                ImGui::Text("...");
                dotNumber = -1;
                break;
            }
            dotNumber++;
            sleep(1);
        }
    }
    ImGui::End();

    ImGui::Render();

    glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::drawJoiningRoom(char *name, bool &submit)
{
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(435, 350));
    ImGui::SetNextWindowSize(ImVec2(200, 100));
    if (ImGui::Begin("TYPE NAME", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetNextWindowPos(ImVec2(435, 350));
        ImGui::SetNextWindowSize(ImVec2(200, 100));
        if (submitedSecond == false)
        {
            ImGui::SetCursorPosX(35);
            ImGui::Text("Your name :");
            ImGui::SetCursorPosX(35);
            ImGui::InputText("##1", name, CHAR_MAX);
            ImGui::SetCursorPosX(35);
            if (ImGui::Button("Submit", ImVec2(130, 40)))
            {
                submit = true;
                submitedSecond = true;
            }
        }
    }
    ImGui::End();

    ImGui::Render();

    glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::quit()
{
    glfwTerminate();
}