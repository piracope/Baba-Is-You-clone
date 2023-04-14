#ifndef VIEW_H
#define VIEW_H

#include "../observer/observer.h"
#include "../model/baba.h"

namespace view
{ // TODO : document view

class ViewConsole : public Observer
{
    model::Baba * baba_;
public:
    explicit ViewConsole(model::Baba * baba);
    ~ViewConsole();
    void update(const Subject * subject) override;
    std::string askLine();
};
}
#endif // VIEW_H
