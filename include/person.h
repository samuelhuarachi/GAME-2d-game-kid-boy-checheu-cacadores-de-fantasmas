#ifndef PERSON_H
#define PERSON_H


class person
{
    public:
        person();
        virtual ~person();
        jump();
        enum stateOptions {
                    STOP,
                    WALKING,
                    JUMP,
                    FALLEN
                };
        setState();
        int getState();
        setLock();
        bool getLock();

    protected:
        stateOptions state;
        bool lock = false;
    private:
};

#endif // PERSON_H
