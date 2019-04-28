#ifndef ACTUATOR_H
#define ACTUATOR_H
#include <vector>

class Actuator
{
public:
    //xmax, ymax, zmax: ストローク(mm)
    Actuator(int xmax, int ymax, int zmax);

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
    Actuator_Error_Type reset_alarm(ActuatorAxis axis);

    typedef struct{
        Actuator_Error_Type errType;
        //アクチュエーターからのデータを1バイトずつ格納
        std::vector<unsigned char> response;
    }ActuatorResponse;

    //アクチュエータからアラームを取得する
    ActuatorResponse getAlarm(ActuatorAxis axis);

    //アクチュエーターのサーボON/OFF状態を取得
    ActuatorResponse getServoStatus(ActuatorAxis axis);

    //アクチュエーターの現在位置を取得する
    ActuatorResponse getCurrentPosition(ActuatorAxis axis);

    //アクチュエーターが原点復帰完了したかどうか取得
    ActuatorResponse getZeroingCompleted(ActuatorAxis axis);

    //アクチュエーターの移動速度を設定する
    //単位は0.01mm/s
    Actuator_Error_Type setSpeed(ActuatorAxis axis, int speed);

    //アクチュエーターの加速度を設定する
    //単位は0.01m/s^2
    Actuator_Error_Type setAcceleration(ActuatorAxis axis, int acceleration);

    //アクチュエーターの減速度を設定する
    //単位は0.01m/s^2
    Actuator_Error_Type setDeceleration(ActuatorAxis axis, int deceleration);

    //アクチュエーターを指定した距離動かす
    //単位は0.1um
    //移動が完了するまでreturnしないこと
    Actuator_Error_Type moveDistance(ActuatorAxis axis, int distance);

    //アクチュエーターを原点復帰する
    //移動が完了するまでreturnしないこと
    Actuator_Error_Type zero(ActuatorAxis axis);

};

#endif // ACTUATOR_H
