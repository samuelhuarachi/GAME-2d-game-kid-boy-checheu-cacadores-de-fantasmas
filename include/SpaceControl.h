#ifndef SPACECONTROL_H
#define SPACECONTROL_H

class SpaceControl
{
    public:
        SpaceControl();
        virtual ~SpaceControl();
        void teste();
        void setInitialSpace(double value);
        void setFinalSpace(double value);
        void calculateExecutionFrame();
        void setPristine(bool value);
        bool getPristine();
        void setVariation(double value);
        double getVariation();
        void handle();
        bool isHandleble();
        void setVariationCount(double value);
        double getVariationCount();

    protected:

    private:
        bool pristine;
        double initialSpace;
        double finalSpace;
        double totalFramesToExecuteAction;
        double variation;
        double variationCount;
};

#endif // SPACECONTROL_H
