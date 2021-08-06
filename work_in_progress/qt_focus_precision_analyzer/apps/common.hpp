#ifndef COMMON_HPP
#define COMMON_HPP

#include <QWidget>

struct CanvasPosition
{
    int x, y;

    // Constructors and Destructors
    CanvasPosition() : x(-1), y(-1) { }
    CanvasPosition(int new_x, int new_y) : x(new_x), y(new_y) { }
    CanvasPoistion(const CanvasPosition& other) : x(other.x), y(other.y) { }
    ~CanvasPosition() { }

    // Methods
    bool equalTo(const CanvasPosition& other) {
        return ((other.x == x) && (other.y == y)) ? true : false;
    }

    // Operators
    bool operator==(const CanvasPosition& other) { return equalTo(other); }
    bool operator!=(const CanvasPosition& other) { return !equalTo(other); }

};


struct TableIndex
{
    int row, column;

    TableIndex() : row(-1), column(-1) { }
    TableIndex(int new_row, int new_column)
        : row(new_row), column(new_column) { }
    TableIndex(const TableIndex& other)
        : row(other.row), column(other.column) { }
    ~TableIndex() { }

    // Methods
    bool equalTo(const TableIndex& other) {
        return ((other.row == row) && (other.column == column)) ? true : false;
    }

    // Operators
    bool operator==(const TableIndex& other) { return equalTo(other); }
    bool operator!=(const TableIndex& other) { return !equalTo(other); }

};


template <class T>
class ActionRequest
{
protected:
    const QWidget* sender_;
    unsigned int action_id_;
    T data_;


public:
    // Constants
    enum GeneralRequest : unsigned int { NoAction=0 };
    enum CustomHeaderRequest : unsigned int {
        SetPrecision=10,
        DuplicateColumn=11
    };

    // Constructors and Destructors
    ActionRequest() : sender_(nullptr), action_id_(ActionRequest::NoAction) { }
    ActionRequest(
            const QWidget* sender,
            unsigned int action_id=ActionRequest::NoAction
            )
        : sender_(sender), action_id_(action_id) { }
    ActionRequest(const ActionRequest& other)
        : sender_(other.sender()), action_id_(other.action_id()) { }
    ~ActionRequest() { }

    // Public methods
    T attachData(T data) { return data_ = data; }
    const QWidget* sender() const { return sender_; }
    unsigned int action_id() const { return action_id_; }
    T data() const { return data_; }

};


class UserOption
{
private:
    QString title_;
    unsigned int action_id_;

public:
    // Constructors and Destructors
    UserOption() : title_("None"), action_id_(ActionRequest::NoAction) { }
    UserOption(QString title, unsigned int action_id)
        : title_(title), action_id_(action_id) { }
    UserOption(const UserOption& other)
        : title_(other.title()), action_id_(other.action_id()) { }
    ~UserOption() { }

    // Public methods
    QString title() const { return title_; }
    unsigned int action_id() const { return action_id_; }

};


#endif  // COMMON_HPP
