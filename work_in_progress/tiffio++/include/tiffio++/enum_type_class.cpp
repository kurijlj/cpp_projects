// Example program
#include <cstdlib>
#include <iostream>
#include <string>


class Container {
public:
    template <class T>
    class EnumeratedType {
    protected:
        T value_;

    public:
        EnumeratedType() {}
        EnumeratedType(T value) : value_(value) {}
        ~EnumeratedType() {}

        // Methods
        virtual std::string str() const = 0;
        virtual const char* c_str() const = 0;

        bool equalTo(const EnumeratedType &other) const {
            return (other.value() == value_ ? true : false);
        }
        T value() const { return value_; }

        // Operators
        bool operator==(const EnumeratedType &other) { return equalTo(other); }
        bool operator!=(const EnumeratedType &other) { return !equalTo(other); }

    };

    class Direction : public EnumeratedType<unsigned short> {
    public:
        enum Directions: unsigned int {
            None = 1,
            Up = 2,
            Down = 3,
            Left = 4,
            Right = 5,
        };

        Direction() : EnumeratedType(Direction::None) {}
        Direction(Direction::Directions value) : EnumeratedType(value) {}
        ~Direction() {}

        // Methods
        std::string str() const {
            std::string result {""};

            switch(value_) {
                case Direction::None: result.append("None"); break;
                case Direction::Up: result.append("Up"); break;
                case Direction::Down: result.append("Down"); break;
                case Direction::Left: result.append("Left"); break;
                case Direction::Right: result.append("Right"); break;
            };

            return result;
        };
        const char* c_str() const { return str().c_str(); }

    };

    Container();
    ~Container();
};


int main()
{
  Container::Direction d1, d2 {Container::Direction::Left};

  std::cout << d1.str() << "\n";
  std::cout << d2.str() << "\n\n";

  return EXIT_SUCCESS;
}
