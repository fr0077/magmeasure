#ifndef PROBE_H
#define PROBE_H


class Probe
{
public:
    Probe();
    //ホールプローブを初期化する
    //戻り値：成功なら0、失敗ならそれ以外
    //すでに初期化済みであってもこの関数を呼び出しても問題ないようにする
    int initialize();

    //ホールプローブをゼロリセットする
    //戻り値：成功なら0、失敗ならそれ以外
    int setZero();

    //ホールプローブの値
    typedef struct {
      //成功なら0、失敗ならそれ以外
      int status;
      //3軸の値
      double x,y,z;
    }Value;

    //プローブの値を出力する
    Value getValue();
};

#endif // PROBE_H
