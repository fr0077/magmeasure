#ifndef ACTUATOR_H
#define ACTUATOR_H
#include <vector>
#include <string>

class Actuator
{
public:
    //xmax, ymax, zmax: ストローク(mm)
    Actuator(int xmax, int ymax, int zmax){
        limits.xmax = xmax;
        limits.ymax = ymax;
        limits.zmax = zmax;
    }

    virtual ~Actuator(){}

    typedef struct{
        int xmax, ymax, zmax;
    }Limits;

    Limits getLimits(){
        return limits;
    }

    enum ActuatorAxis{
      ACTUATOR_AXIS_X,ACTUATOR_AXIS_Y,ACTUATOR_AXIS_Z
    };

    enum Direction{
        POSITIVE, NEGATIVE
    };

    static std::string axis_toString(ActuatorAxis axis){
        if(axis == ACTUATOR_AXIS_X)
            return "X";
        if(axis == ACTUATOR_AXIS_Y)
            return "Y";
        if(axis == ACTUATOR_AXIS_Z){
            return "Z";
        }
    }

    static std::string direction_toString(Actuator::Direction d){
        if(d == Actuator::Direction::POSITIVE){
            return "PLUS";
        }

        if(d == NEGATIVE){
            return "MINUS";
        }
    }

    enum Actuator_Error_Type{
        //アクチュエーターはコマンドを正常に実行した
        COMMAND_SUCCESS = 0,
        //アクチュエーターがコマンド実行失敗を返した
        COMMAND_FAILED,
        //アクチュエーターからコマンドに対し応答がない
        TIMED_OUT,
    };

    static std::string error_toString(Actuator_Error_Type t ){
        if(t == COMMAND_SUCCESS){
            return "SUCCESS";
        }

        if(t == COMMAND_FAILED){
            return "FAILED";
        }

        if(t == TIMED_OUT){
            return "TIMED_OUT";
        }
    }

    virtual Actuator_Error_Type init(ActuatorAxis axis) = 0;

    //アラームをリセットする
    virtual Actuator_Error_Type resetAlarm(ActuatorAxis axis) = 0;

    typedef struct{
        Actuator_Error_Type errType;
        //アクチュエーターからのデータを1バイトずつ格納
        std::vector<std::string> response;
    }ActuatorResponse;


    virtual int realPosition_bytesToInt(ActuatorResponse response) = 0;

    virtual int indicatedPosition_bytesToInt(ActuatorResponse response) = 0;

    //アクチュエータからアラームを取得する
    virtual ActuatorResponse getAlarm(ActuatorAxis axis) = 0;

    //アクチュエーターのサーボON/OFF状態を取得
    virtual ActuatorResponse getServoStatus(ActuatorAxis axis) = 0;

    //アクチュエーターの現在位置を取得する
    virtual ActuatorResponse getCurrentPosition(ActuatorAxis axis) = 0;

    //アクチュエーターの移動速度を設定する
    //単位は0.01mm/s
    virtual Actuator_Error_Type setSpeed(ActuatorAxis axis, int speed) = 0;

    //アクチュエーターの移動距離を設定する
    //単位は0.1um
    virtual Actuator_Error_Type setDistance(ActuatorAxis axis, int dist) = 0;

    //アクチュエータを移動する
    //移動が完了するまでreturnしないこと
    virtual Actuator_Error_Type move(ActuatorAxis axis, Direction d) = 0;

    //アクチュエーターを原点復帰する
    //移動が完了するまでreturnしないこと
    virtual Actuator_Error_Type zero(ActuatorAxis axis) = 0;

    virtual Actuator_Error_Type servoOn(ActuatorAxis axis) = 0;

private:
    Limits limits;
};

#endif // ACTUATOR_H
