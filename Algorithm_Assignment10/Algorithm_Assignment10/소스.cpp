/*
 * k대의 초정밀측정기를 가진 연구기관
 * 검사는 하루가 걸린다
 * 미리 요청을 받은 작업을 바탕으로 1일부터 T일까지의 작업을 미리 확정하고자 한다
 * 작업(Task) ti의 요청은 처리해주면 ci의 비용과 원하는 마감날짜 di로 구성되어 있다
 * 작업을 처리해 줄 경우에는 반드시 마감일을 넘지 않아야 한다
 * 따라서 마감일 이전에 미리 작업을 처리하는 것은 가능하고, 처리할 수 없는 의뢰는 다시 돌려보낸다
 *
 * 근데 작업에 최선을 다하지 않기로 했다
 * 얻을 수 있는 이익중에서 최대가 아닌 차순위 단계의 이득을 받을 정도만 일을 하기로 했다
 * ==> 주어진 N개의 작업을 k개의 기계로 처리할 때 얻을 수 있는 최대이득과 가능한 차순위의 최대이득
 * 즉 2번째로 높은 이득을 계산해야한다
 * 최대이득은 Greedy Algorithm으로 구할 수 있다
 * 그러나 최대 이득이 아닌 차순위 이득을 구하라
 */