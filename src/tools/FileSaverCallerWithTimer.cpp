#include "stdafx.h"

#include <thread>
#include <Windows.h>

#include "FileSaverCallerWithTimer.h"
#include "FileSaver.h"
#include "renderer/Renderer.h"

using namespace std;

namespace OmochiRenderer {

  FileSaverCallerWithTimer::FileSaverCallerWithTimer(std::weak_ptr<Renderer> renderer, std::shared_ptr<FileSaver> saver)
    : m_renderer(renderer)
    , m_saver(saver)
    , m_thread()
    , m_stopSignal(false)
    , m_saveSpan(0)
    , m_lastSaveTime(0)
  {
  }

  bool FileSaverCallerWithTimer::StartTimer()
  {
    // タイマーを始められる条件をチェック
    if (m_saveSpan == 0) return false;
    if (m_renderer.expired()) return false;
    if (m_saver == nullptr) return false;

    // 2つ以上走らせない
    if (m_thread != nullptr) {
      StopAndWaitStopping();
    }

    m_stopSignal = false;
    m_thread = std::shared_ptr<std::thread>(new std::thread(
      [this]() {
        
        clock_t start = 0, end = 0;
        double saveSpan = m_saveSpan*1000;
        double accTime = 0;
        double accDiff = 0;

        while (!m_stopSignal) {

          // Sleep しつつ実時間計測
          cerr << "Begin sleeping...: Sleep(static_cast<DWORD>(" << saveSpan + accDiff << ")" << endl;
          start = clock();
          Sleep(static_cast<DWORD>(saveSpan + accDiff));

          // 保存実行
          double tmpAccTime = accTime + 1000.0*(clock() - start) / CLOCKS_PER_SEC;
          if (std::shared_ptr<Renderer> render = m_renderer.lock())
          {
            m_saver->Save(render->GetCurrentSampleCount(), render->GetResult(), tmpAccTime / 1000.0 / 60);
          }
          else
          {
            // レンダラが消えていたのでおしまい
            break;
          }

          end = clock();

          // ぴったり合わなかった時間を次に持越し
          double pastTime = 1000.0*(end - start) / CLOCKS_PER_SEC;
          accDiff += saveSpan - pastTime;

          cerr << pastTime << " second past." << endl;
          accTime += pastTime;

        }

        m_thread.reset();
      }
    ));

    return true;
  }

  void FileSaverCallerWithTimer::StopAndWaitStopping()
  {
    if (m_thread == nullptr) return;

    m_stopSignal = true;
    m_thread->join();
  }
}
