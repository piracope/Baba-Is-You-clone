#ifndef VIEW_H
#define VIEW_H

#include "../observer/observer.h"
#include "../model/baba.h"

namespace view
{//retirer namesapce

class ViewConsole : public Observer
{
    model::Baba * baba_;
public:
    explicit ViewConsole(model::Baba * baba);
    ~ViewConsole();
    void update(const Subject * subject) override;
};
}
#endif // VIEW_H
