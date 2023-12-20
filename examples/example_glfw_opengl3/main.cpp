#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

// 定义多项式结构体
typedef struct PNode {
    float coef;      // 系数
    int expn;        // 指数
    struct PNode* next; // 指针域
} PNode, * polynomial;

// 创建多项式
void creatlist(polynomial& p) {
    // 输入n项的系数和指数，建立表示多项式的有序链表p
    p = new PNode; // 为链表P1申请一个空间;
    int n;
    std::cout << "请输入多项式项数：";
    std::cin >> n;
    p->next = NULL; // 建立一个带头节点的单链表
    polynomial t, q; // 用于标记位置
    for (int i = 1; i <= n; i++) {
        // 依次输入n个非零项，并将它们排序
        polynomial s = new PNode; // 生成一个新节点，用于存储输入的系数和指数
        std::cout << "请分别输入系数和指数: ";
        std::cin >> s->coef >> s->expn; // 输入系数和指数
        t = p; // t用于保存q的前驱，初值为头节点，为了让p只表示头节点
        q = p->next; // q初始化，指向首元节点
        while (q && q->expn < s->expn) {
            // 从头到尾开始比较指数找到第一个大于输入指数的项*q
            t = q;
            q = q->next; // q指向下一个节点
        } // while
        s->next = q; // 将输入项s插入到q和其他前驱节点pre之间
        t->next = s;
    } // for
}

// 输出多项式
void printout(polynomial p) {
    int n = 0;
    polynomial t = p;
    while (t && (t = t->next)){
        n++; // 多项式项数
    } // while
    p = p->next;
    for (int i = 1; i < n; i++) {
        if (p->coef != 0 && p->expn == 0) // 判断是否为常数项
            std::cout << p->coef << "+";
        else if (p->coef < 0) {
            std::cout << "\b";
            std::cout << p->coef << "x^" << p->expn << "+";
        }
        else
            std::cout << p->coef << "x^" << p->expn << "+";
        p = p->next;
    }
    // 单独输出最后一项
    if (p->coef < 0) {
        std::cout << "\b";
        std::cout << p->coef << "x^" << p->expn;
    }
    else
        std::cout << p->coef << "x^" << p->expn;
}

// 多项式加法
void add_polynomial(polynomial p1, polynomial p2) {
    polynomial t = p1; // t指向p1的头节点
    polynomial flag = t; // 用来标记p1的头节点
    p1 = p1->next;
    p2 = p2->next; // p1, p2分别指向首元节点
    while (p1 && p2) {
        if (p1->expn == p2->expn) {
            p1->coef += p2->coef;
            if (p1->coef) {
                t->next = p1;
                t = p1;
                p1 = p1->next;
                polynomial r = p2;
                p2 = p2->next;
                delete r;
            }
            else {
                polynomial r = p1;
                p1 = p1->next;
                delete r;
                polynomial rr = p2;
                p2 = p2->next;
                delete rr;
            }
        }
        else if (p1->expn < p2->expn) {
            t->next = p1;
            t = p1;
            p1 = p1->next;
        }
        else {
            t->next = p2;
            t = p2;
            p2 = p2->next;
        }
    } // while
    t->next = p1 ? p1 : p2;
    std::cout << "相加的结果为：" << std::endl;
    printout(flag);
    delete p2;
}

// 多项式减法
void subtruct_polynomial(polynomial p1, polynomial p2) {
    polynomial t = p1; // t指向p1的头节点
    polynomial flag = t; // 用来标记p1的头节点
    p1 = p1->next;
    p2 = p2->next; // p1, p2分别指向首元节点
    while (p1 && p2) {
        if (p1->expn == p2->expn) {
            p1->coef -= p2->coef;
            if (p1->coef) {
                t->next = p1;
                t = p1;
                p1 = p1->next;
                polynomial r = p2;
                p2 = p2->next;
                delete r;
            }
            else {
                polynomial r = p1;
                p1 = p1->next;
                delete r;
                polynomial rr = p2;
                p2 = p2->next;
                delete rr;
            }
        }
        else if (p1->expn < p2->expn) {
            t->next = p1;
            t = p1;
            p1 = p1->next;
        }
        else {
            p2->coef *= -1;
            t->next = p2;
            t = p2;
            p2 = p2->next;
        }
    } // while
    if (p1)
        t->next = p1;
    if (p2)
        while (p2) {
            p2->coef *= -1;
            t->next = p2;
            t = p2;
            p2 = p2->next;
        }
    std::cout << "相减的结果为：" << std::endl;
    printout(flag);
    delete p2;
}

// 排序函数
void sort(polynomial p, polynomial head) {
    p = head;
    polynomial t1 = p->next;
    polynomial t2 = p->next;
    polynomial t3 = NULL;
    float ct;
    int et;
    while (t2 != t3) {
        while (t1->next != t3) {
            if ((t1->expn) > (t1->next->expn)) {
                ct = t1->coef;
                t1->coef = t1->next->coef;
                t1->next->coef = ct;
                et = t1->expn;
                t1->expn = t1->next->expn;
                t1->next->expn = et;
            }
            t1 = t1->next;
        }
        t3 = t1;
        t1 = p->next;
    }
}

// 多项式乘法
void multiply_polynomial(polynomial& p1, polynomial& p2) {
    polynomial head2 = p2;
    polynomial head = new PNode;
    polynomial flag;
    flag = head;
    p1 = p1->next;
    p2 = p2->next;
    while (p1) {
        while (p2) {
            polynomial t = new PNode;
            t->coef = p1->coef * p2->coef;
            t->expn = p1->expn + p2->expn;
            flag->next = t;
            t->next = NULL;
            flag = t;
            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = head2->next;
    }
    sort(flag, head);
    for (polynomial q = head->next; q && q->next;) {
        if (q->expn == q->next->expn) {
            q->coef += q->next->coef;
            q->next = q->next->next;
        }
        else
            q = q->next;
    }
    std::cout << "相乘的结果为：" << std::endl;
    printout(head);
}

// 菜单函数
void display() {
    std::cout << "========================" << std::endl;
    std::cout << "1.创建多项式" << std::endl;
    std::cout << "2.多项式加法" << std::endl;
    std::cout << "3.多项式减法" << std::endl;
    std::cout << "4.多项式乘法" << std::endl;
    std::cout << "0.退出" << std::endl;
    std::cout << "========================" << std::endl;
}

// Function to draw the polynomial on the SFML window
void drawPolynomial(sf::RenderWindow& window, polynomial p, sf::Color color, float startX, float endX) {
    sf::VertexArray line(sf::LineStrip);

    for (float x = startX; x <= endX; x += 0.1) {
        float y = 0;
        polynomial temp = p;

        while (temp) {
            y += temp->coef * pow(x, temp->expn);
            temp = temp->next;
        }

        sf::Vertex point(sf::Vector2f(x * 50, y * 50), color);
        line.append(point);
    }

    window.draw(line);
}

// Function to destroy the polynomial and free memory
void destroyPolynomial(polynomial& p) {
    polynomial temp;
    while (p) {
        temp = p;
        p = p->next;
        delete temp;
        temp = nullptr;  // 将 temp 设置为 nullptr，防止悬挂指针问题
    }
}

int main() {
    // SFML window setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Polynomial Calculator");
    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    int n;
    polynomial p1 = nullptr;
    polynomial p2 = nullptr;

    char buffer1[256] = "";
    char buffer2[256] = "";

    display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            ImGui::SFML::ProcessEvent(event);
        }

        ImGui::SFML::Update(window, sf::seconds(0.0f));

        std::cout << "请输入要执行的操作：";
        std::cin >> n;

        switch (n) {
        case 1:
            // Create polynomials using ImGui for input
            ImGui::Begin("Polynomial Input");
            ImGui::InputText("Polynomial 1", buffer1, sizeof(buffer1));
            ImGui::InputText("Polynomial 2", buffer2, sizeof(buffer2));
            if (ImGui::Button("Submit")) {
                // Parse buffer1 and buffer2 to create polynomials p1 and p2
                // (You need to implement a function to parse the input strings)
                // Example: parseInput(buffer1, p1);
                // Example: parseInput(buffer2, p2);
                std::cout << "第一个多项式为：";
                printout(p1);
                std::cout << std::endl;
                std::cout << "第二个多项式为：";
                printout(p2);
                std::cout << std::endl;

                ImGui::End();
                break;
            }
            ImGui::End();
            break;
        case 2:
            // 多项式相加
            add_polynomial(p1, p2);
            std::cout << std::endl;
            break;
        case 3:
            // 多项式减法
            subtruct_polynomial(p1, p2);
            std::cout << std::endl;
            break;
        case 4:
            // 多项式相乘
            multiply_polynomial(p1, p2);
            std::cout << std::endl;
            break;
        case 0:
            // Deallocate memory and exit
            destroyPolynomial(p1);
            destroyPolynomial(p2);
            window.close();
            break;
        default:
            std::cout << "输入不合法，请重新输入！" << std::endl;
            std::cout << std::endl;
            break;
        }

        // Draw the polynomials on the SFML window
        window.clear();
        drawPolynomial(window, p1, sf::Color::Red, -10, 10);
        drawPolynomial(window, p2, sf::Color::Blue, -10, 10);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    destroyPolynomial(p1);
    destroyPolynomial(p2);

    return 0;
}
