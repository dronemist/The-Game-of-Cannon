for run in {1..10}
do
x-terminal-emulator -e bash run_server.sh
x-terminal-emulator -e bash run_learner.sh
bash run_best.sh
python analyse_results.py
done