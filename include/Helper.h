#ifndef HELPER_H
#define HELPER_H


class Helper
{
    public:
        Helper();
        virtual ~Helper();
        void writeSomeTextInCmd(std::string text = "default text", bool DEBUG_ACTIVATED = false);

    protected:

    private:
};

#endif // HELPER_H
