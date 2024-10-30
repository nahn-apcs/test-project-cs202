#include <SFML/Graphics.hpp>

int main() {
    // Tạo cửa sổ SFML với kích thước 800x600 và tiêu đề "SFML Cơ Bản"
    sf::RenderWindow window(sf::VideoMode(800, 600), "helu");

    // Tạo một hình tròn với bán kính 50 pixel và đặt màu là xanh lam
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Blue);

    // Đặt vị trí ban đầu của hình tròn ở giữa màn hình
    float xPosition = 375.0f; // Vị trí X
    float yPosition = 275.0f; // Vị trí Y
    circle.setPosition(xPosition, yPosition);

    // Tốc độ di chuyển của hình tròn
    float speed = 200.0f;

    // Vòng lặp chính của chương trình
    while (window.isOpen()) {
        // Xử lý sự kiện
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Cập nhật vị trí hình tròn
        if (xPosition <= 0 || xPosition >= 750)
            speed = -speed; // Đảo ngược hướng khi chạm biên
        xPosition += speed * 0.01f; // Di chuyển hình tròn
        circle.setPosition(xPosition, yPosition);

        // Xóa màn hình với màu đen
        window.clear(sf::Color::Black);

        // Vẽ hình tròn lên cửa sổ
        window.draw(circle);

        // Hiển thị nội dung của cửa sổ
        window.display();
    }

    return 0;
}
