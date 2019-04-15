#ifndef ACTUATOR_H
#define ACTUATOR_H


class Actuator
{
public:
    Actuator(int xmax, int ymax, int zmax);
    //アクチュエーターを初期化する
    //戻り値：成功なら0、失敗ならそれ以外
    int initialize();

    //鉛直をY向きとし、ビーム方向をZとする。右手系。
    enum Axis{
      X,Y,Z
    };

    //アクチュエーターの移動速度を設定する
    //単位は0.01mm/s
    //戻り値：成功なら0、失敗ならそれ以外
    int setSpeed(Axis axis, int speed);

    //アクチュエーターの加速度を設定する
    //単位は0.01m/s^2
    //戻り値：成功なら0、失敗ならそれ以外
    int setAcceleration(Axis axis, int acceleration);

    //アクチュエーターの減速度を設定する
    //単位は0.01m/s^2
    //戻り値：成功なら0、失敗ならそれ以外
    int setDeceleration(Axis axis, int deceleration);

    //アクチュエーターを停止する
    //戻り値：成功なら0、失敗ならそれ以外
    int halt();

    //アクチュエーターを指定した距離動かす
    //単位は0.1um
    //戻り値：成功なら0、失敗ならそれ以外
    //移動が終わるまでreturnしてはいけない
    int moveDistance(Axis axis, int distance);

    //アクチュエーターを原点復帰する
    //障害物が近くにない状態で実行しなければならない
    //戻り値：成功なら0、失敗ならそれ以外
    int zero(Axis axis);

};

#endif // ACTUATOR_H
