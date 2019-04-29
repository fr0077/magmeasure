#ifndef ACTUATOR_H
#define ACTUATOR_H
#include <vector>

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

    enum Actuator_Error_Type{
        //アクチュエーターはコマンドを正常に実行した
        COMMAND_SUCCESS = 0,
        //アクチュエーターがコマンド実行失敗を返した
        COMMAND_FAILED,
        //アクチュエーターからコマンドに対し応答がない
        TIMED_OUT,
    };

    //アラームをリセットする
    virtual Actuator_Error_Type resetAlarm(ActuatorAxis axis) = 0;

    typedef struct{
        Actuator_Error_Type errType;
        //アクチュエーターからのデータを1バイトずつ格納
        std::vector<unsigned char> response;
    }ActuatorResponse;

    //アクチュエータからアラームを取得する
    virtual ActuatorResponse getAlarm(ActuatorAxis axis) = 0;

    //アクチュエーターのサーボON/OFF状態を取得
    virtual ActuatorResponse getServoStatus(ActuatorAxis axis) = 0;

    //アクチュエーターの現在位置を取得する
    virtual ActuatorResponse getCurrentPosition(ActuatorAxis axis) = 0;

    //アクチュエーターが原点復帰完了したかどうか取得
    virtual ActuatorResponse getZeroingCompleted(ActuatorAxis axis) = 0;

    //アクチュエーターの移動速度を設定する
    //単位は0.01mm/s
    virtual Actuator_Error_Type setSpeed(ActuatorAxis axis, int speed) = 0;

    //アクチュエーターの加速度を設定する
    //単位は0.01m/s^2
    virtual Actuator_Error_Type setAcceleration(ActuatorAxis axis, int acceleration) = 0;

    //アクチュエーターの減速度を設定する
    //単位は0.01m/s^2
    virtual Actuator_Error_Type setDeceleration(ActuatorAxis axis, int deceleration) = 0;

    //アクチュエーターを指定した距離動かす
    //単位は0.1um
    //移動が完了するまでreturnしないこと
    virtual Actuator_Error_Type moveDistance(ActuatorAxis axis, int distance) = 0;

    //アクチュエーターを原点復帰する
    //移動が完了するまでreturnしないこと
    virtual Actuator_Error_Type zero(ActuatorAxis axis) = 0;

private:
    Limits limits;
};

#endif // ACTUATOR_H
