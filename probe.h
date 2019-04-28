#ifndef PROBE_H
#define PROBE_H


class Probe
{
public:
    enum ProbeAxis{
      PROBE_AXIS_X,PROBE_AXIS_Y,PROBE_AXIS_Z
    };

    enum ProbeErrorType{
        //プローブはコマンドを正常に実行した
        COMMAND_SUCCESS = 0,
        //プローブがコマンド実行失敗を返した
        COMMAND_FAILED,
        //プローブからコマンドに対し応答がない
        TIMED_OUT,
    };

    //プローブを初期化する
    ProbeErrorType initialize();

    //ホールプローブをゼロリセットする
    ProbeErrorType setZero(ProbeAxis axis);

    //ホールプローブの値
    typedef struct {
      //成功なら0、失敗ならそれ以外
      ProbeErrorType status;
      //3軸の値
      double x,y,z;
    }Value;

    //プローブの値を出力する
    Value getValue();
};

#endif // PROBE_H
