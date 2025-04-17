
# STM32F4 base code

- STM32F4 마이크로컨트롤러(STM32F407VGT6) 기반 base code

- 다음과 같은 기능 제공
    - 실시간 제어를 위한 TIM Interrupt
    - 모터 제어용 PWM 및 엔코더 module
    - 16채널 IR 센서를 위한 ADC module
    - UART 기반 디버깅 기능

---

## Features

- PID 기반 듀얼 모터 속도 제어
- QEP(Quadrature Encoder Pulse) 방식의 엔코더 피드백 처리 (TIM1, TIM8)
- PWM 모터 제어 출력 (TIM3)
- 16채널 ADC 센서 데이터 수집 (DMA 포함)
- UART 디버깅 메시지 출력 (`TxPrintf` 사용)
- 타이머 기반 주기적 제어 루프 (모터: TIM4, 센서: TIM9)

---

## Peripheral

| Peripheral | 역할 |
|------------|------|
| TIM1 / TIM8 | 엔코더 입력 (좌/우 모터) |
| TIM3       | PWM 출력 (모터 구동용) |
| TIM4       | 모터 제어용 인터럽트 (0.25 ms 주기) |
| TIM9       | 센서 처리용 인터럽트 (25 μs 주기) |
| ADC1       | 16채널 아날로그 센서 입력 (DMA 사용) |
| UART4 / USART1 | 디버깅 및 외부 통신용 UART |

---

## 주요 파일

### `main.c`
- HAL, 클럭, 주변장치 초기화
- 타이머 및 엔코더 시작

### `motor.c`
- 좌/우 모터 PID 속도 제어
- 가속/감속 로직
- `TIM4` 인터럽트에서 주기적 제어 수행

### `tim.c`
- 타이머 설정 (TIM1, TIM3, TIM4, TIM8, TIM9)
- PWM 출력 및 엔코더 입력, 인터럽트 기반 제어 루프 주기 설정

### `adc.c`
- 16개 ADC 채널 설정
- GPIOA, B, C 핀에 연결됨

### `gpio.c`
- 모든 입출력 핀 및 PWM, UART, VFD 제어 핀 설정

### `usart.c`
- UART4 / USART1 설정
- `TxPrintf()` 함수 구현
---

## 디버깅

- `TxPrintf()` → UART 출력용 디버깅 함수
- ISR 타이밍 확인용 GPIO 토글

---

## 참고 사항

- STM32CubeMX 기반 프로젝트이며 HAL 드라이버 사용
- 모든 타이머 주기는 APB1(84MHz), APB2(168MHz) 클럭 기준으로 설정됨
- PID 상수는 `motor.c`에서 조정 가능

---

## 📂 디렉토리 구조

```
Core/
├── Src/
│   ├── main.c
│   ├── motor.c
│   ├── tim.c
│   ├── adc.c
│   ├── dma.c
│   ├── gpio.c
│   ├── usart.c
├── Inc/
│   └── [헤더 파일들]
Drivers/
├── STM32F4xx_HAL_Driver
├── CMSIS
```

---

## 제작자
- 김진성
- 이진호