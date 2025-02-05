# Simulação de Temporizador One Shot com Raspberry Pi Pico W no Wokwi

## 📌 Descrição
Este projeto implementa um **temporizador de um disparo (One Shot)** utilizando um **Raspberry Pi Pico W** e a API do **Pico SDK**. Quando o botão é pressionado, **três LEDs acendem simultaneamente**, e então são desligados **um por um a cada 3 segundos**.

A simulação foi desenvolvida e testada na plataforma **Wokwi**, garantindo um ambiente de simulação realista para sistemas embarcados.

---

## 📜 Funcionalidades
✅ **Pressionar o botão liga os três LEDs.**  
✅ **Após 3 segundos, o primeiro LED se apaga.**  
✅ **Após mais 3 segundos, o segundo LED se apaga.**  
✅ **Após mais 3 segundos, o último LED se apaga.**
✅ **Pressionar o botão liga os três LEDs.**  
✅ **Após mais 3 segundos, o LED verde se apaga.** 
✅ **O botão só pode ser pressionado novamente após o ciclo completo.**  
✅ **Implementação de debounce para evitar leituras erradas do botão.**  

---

## 🛠️ Configuração do Hardware
### **Componentes Utilizados:**
- **Microcontrolador:** Raspberry Pi Pico W
- **LEDs:** Azul, Vermelho e Verde
- **Resistores:** 330Ω para cada LED
- **Pushbutton:** Botão conectado ao GPIO 5

### **Conexões dos LEDs e Botão no Pico W:**
| Componente | GPIO |
|------------|------|
| Botão      | 5    |
| LED Azul   | 11   |
| LED Vermelho | 12  |
| LED Verde  | 13   |

---

## 🖥️ Como Executar no Wokwi
1. **Abra o Wokwi** e crie um novo projeto com o Raspberry Pi Pico W.
2. **Adicione os arquivos do projeto** (`oneshot.c`, `CMakeLists.txt`, `diagram.json`, `wokwi.toml`).
3. **Configure o `wokwi.toml`** para garantir que o firmware correto está sendo carregado.
4. **Compile e execute a simulação.**
5. **Acompanhe as mensagens no monitor serial** para visualizar os estados dos LEDs e do botão.

---

## 📂 Estrutura do Projeto
```
├── oneshot.c        # Código principal em C
├── CMakeLists.txt   # Configuração do CMake para compilação
├── diagram.json     # Configuração dos componentes no Wokwi
├── wokwi.toml       # Configuração do firmware no Wokwi
├── README.md        # Documentação do projeto
```

---

## 📝 Notas
- Este projeto foi desenvolvido para simulação no **Wokwi**, mas pode ser adaptado para rodar em hardware real.


## 👨‍💻 Autor
**Kauan Teixeira da Hora**




