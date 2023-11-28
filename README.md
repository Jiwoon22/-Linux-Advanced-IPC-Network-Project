
<br>
<h1 align="center"> IPC 통신 기법을 활용한 음악 퀴즈 프로그램 </h1>
<br>

---
### [설계 과제 목표]
* IPC 통신기법의 이해
* PIPE, Message Passing, Shared Memory 기법 적용
* 각 기법의 성능 분석
 
### [요구사항 분석]
* 클라이언트간의 원활한 통신
* 쓰레드의 병행
* 경쟁상태 방지, 동기화 기법 사용
<br/>

***1. PIPE 소프트웨어 설계도와 쓰레드 설계***  
<br/>
- 소프트웨어 설계도  <br/>
![image](https://github.com/Jiwoon22/Advanced-IPC-Network-Project/assets/51106092/f060416c-d1b4-44de-ba8a-2996a8c8a1c3)    
<br/><br/>
- 쓰레드 설계  <br/>
![image](https://github.com/Jiwoon22/Advanced-IPC-Network-Project/assets/51106092/b8ec9951-974a-4ebe-aea5-dd4bd544ba9b)    
<br/><br/>





***2. Message Passing 소프트웨어 설계도와 쓰레드 설계***  
<br/>
- 소프트웨어 설계도  <br/>
![image](https://github.com/Jiwoon22/Advanced-IPC-Network-Project/assets/51106092/e85a751c-b657-4da6-9184-ad8aa304bc80)
<br/><br/>
- 쓰레드 설계  <br/>
![image](https://github.com/Jiwoon22/Advanced-IPC-Network-Project/assets/51106092/26dd9d18-cdcc-4b9e-9777-09dd993df3cd)
<br/><br/><br/>





***3. Shared Memory 소프트웨어 설계도와 쓰레드 설계*** 
<br/>
- 소프트웨어 설계도  <br/>
![image](https://github.com/Jiwoon22/Advanced-IPC-Network-Project/assets/51106092/d4036171-ea9b-4de4-a79d-1d9a02842ebd)
<br/><br/>

- 쓰레드 설계  <br/>
![image](https://github.com/Jiwoon22/Advanced-IPC-Network-Project/assets/51106092/4a49341e-a7d4-42dd-9124-e3f94ba6b5b3)



