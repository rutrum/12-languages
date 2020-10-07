import javax.swing.*;
import java.awt.*;

public class Engine {
    public static void main(String[] args) {
        JFrame frame = new JFrame();
        Container pane = frame.getContentPane();
        pane.setLayout(new BorderLayout());

        JSlider headingSlider = new JSlider(0, 360, 180);
        pane.add(headingSlider, BorderLayout.SOUTH);
        JSlider pitchSlider = new JSlider(SwingConstants.VERTICAL, -90, 90, 0);
        pane.add(pitchSlider, BorderLayout.EAST);

        List tris = new ArrayList<>();
        tris.add(new Triangle(new Vertex(100, 100, 100),
                              new Vertex(-100, -100, 100),
                              new Vertex(-100, 100, -100),
                              Color.WHITE));
        tris.add(new Triangle(new Vertex(100, 100, 100),
                              new Vertex(-100, -100, 100),
                              new Vertex(100, -100, -100),
                              Color.RED));
        tris.add(new Triangle(new Vertex(-100, 100, -100),
                              new Vertex(100, -100, -100),
                              new Vertex(100, 100, 100),
                              Color.GREEN));
        tris.add(new Triangle(new Vertex(-100, 100, -100),
                              new Vertex(100, -100, -100),
                              new Vertex(-100, -100, 100),
                              Color.BLUE));

        JPanel renderPanel = new JPanel() {
            public void paintComponent(Graphics g) {
                Graphics2D g2 = (Graphics2D) g; // type casting from generic Graphics
                g2.setColor(Color.RED);
                g2.fillRect(0, 0, getWidth(), getHeight());

                /*
                g2.translate(getWidth() / 2, getHeight() / 2);
                g2.setColor(Color.WHITE);
                Path2D path = new Path2D.Double();
                path.moveTo(20, 20);
                path.lineTo(0, 20);
                path.lineTo(20, 0);
                path.closePath();
                g2.draw(path);
                
                for (Triangle t : tris) {
                    Path2D path = new Path2D.Double();
                    path.moveTo(t.v1.x, t.v1.y);
                    path.lineTo(t.v2.x, t.v2.y);
                    path.lineTo(t.v3.x, t.v3.y);
                    path.closePath();
                    g2.draw(path);
                }
                */
            }
        };
        pane.add(renderPanel, BorderLayout.CENTER);

        frame.setSize(400, 400);
        frame.setVisible(true);


    }
}

class Vertex {
    double x, y, z;

    Vertex(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
}

class Triangle {
    Vertex v1, v2, v3;
    Color color;
    
    Triangle(Vertex v1, Vertex v2, Vertex v3, Color color) {
        this.v1 = v1;
        this.v2 = v2;
        this.v3 = v3;
        this.color = color;
    }
}

class Matrix3 {
    double[] values;

    Matrix3(double[] values) {
        this.values = values;
    }

    Matrix3 multiply(Matrix3 other) {
        double[] reuslt = new double[9];
        for (int row = 0; row < 3; row += 1) {
            for (int col = 0; col < 3; col += 1) {
                for (int i = 0; i < 3; i += 1) {
                    result[row * 3 + col] += 
                        this.values[row * 3 + i] * other.values[i * 3 + col];
                }
            }
        }

        return new Matrix3(result);
    }

    Vertex transform(Vertex in) {
        return new Vertex(
            in.x * values[0] + in.y * values[3] + in.z * values[6], 
            in.x * values[1] + in.y * values[4] + in.z * values[7], 
            in.x * values[2] + in.y * values[5] + in.z * values[8]
        );
    }
}
